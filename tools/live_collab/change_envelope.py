#!/usr/bin/env python3
"""Deterministic envelope + journal primitives for KiCad live collaboration (M1)."""

from __future__ import annotations

import argparse
import hashlib
import json
import time
import uuid
from dataclasses import dataclass
from pathlib import Path
from typing import Any, Dict

SCHEMA_VERSION = 1


@dataclass(frozen=True)
class ChangeEnvelope:
    """A canonical change event shared by all collaboration peers."""

    schema_version: int
    actor_id: str
    document_id: str
    operation: str
    logical_clock: int
    timestamp_ms: int
    nonce: str
    payload: Dict[str, Any]

    def to_dict(self) -> Dict[str, Any]:
        return {
            "schema_version": self.schema_version,
            "actor_id": self.actor_id,
            "document_id": self.document_id,
            "operation": self.operation,
            "logical_clock": self.logical_clock,
            "timestamp_ms": self.timestamp_ms,
            "nonce": self.nonce,
            "payload": self.payload,
        }


def canonical_json(data: Dict[str, Any]) -> str:
    """Stable JSON encoding used for hashing and storage."""
    return json.dumps(data, sort_keys=True, separators=(",", ":"), ensure_ascii=False)


def envelope_hash(envelope: ChangeEnvelope) -> str:
    """SHA-256 over canonical envelope JSON."""
    material = canonical_json(envelope.to_dict()).encode("utf-8")
    return hashlib.sha256(material).hexdigest()


def make_envelope(
    actor_id: str,
    document_id: str,
    operation: str,
    payload: Dict[str, Any],
    logical_clock: int,
    *,
    timestamp_ms: int | None = None,
    nonce: str | None = None,
) -> ChangeEnvelope:
    return ChangeEnvelope(
        schema_version=SCHEMA_VERSION,
        actor_id=actor_id,
        document_id=document_id,
        operation=operation,
        logical_clock=logical_clock,
        timestamp_ms=timestamp_ms if timestamp_ms is not None else int(time.time() * 1000),
        nonce=nonce if nonce is not None else uuid.uuid4().hex,
        payload=payload,
    )


def append_jsonl(path: Path, envelope: ChangeEnvelope) -> str:
    """Append a canonical journal row and return event id."""
    event_id = envelope_hash(envelope)
    row = {
        "event_id": event_id,
        "envelope": envelope.to_dict(),
    }
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("a", encoding="utf-8") as f:
        f.write(canonical_json(row))
        f.write("\n")
    return event_id


def _parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--actor", required=True, help="Actor/user ID")
    parser.add_argument("--document", required=True, help="Document ID (e.g. pcb:<uuid>)")
    parser.add_argument("--op", required=True, help="Operation name")
    parser.add_argument("--payload", required=True, help="JSON object payload")
    parser.add_argument("--clock", type=int, default=1, help="Logical clock value")
    parser.add_argument(
        "--journal",
        default="tools/live_collab/journal/events.jsonl",
        help="Output JSONL journal file",
    )
    return parser.parse_args()


def main() -> int:
    args = _parse_args()
    payload = json.loads(args.payload)
    if not isinstance(payload, dict):
        raise SystemExit("payload must decode to a JSON object")

    envelope = make_envelope(
        actor_id=args.actor,
        document_id=args.document,
        operation=args.op,
        payload=payload,
        logical_clock=args.clock,
    )
    event_id = append_jsonl(Path(args.journal), envelope)
    print(event_id)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
