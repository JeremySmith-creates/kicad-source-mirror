import json
import tempfile
import unittest
from pathlib import Path

from tools.live_collab import change_envelope as ce


class ChangeEnvelopeTests(unittest.TestCase):
    def test_canonical_json_is_stable(self):
        a = {"b": 2, "a": 1, "nested": {"z": 1, "x": 0}}
        b = {"nested": {"x": 0, "z": 1}, "a": 1, "b": 2}
        self.assertEqual(ce.canonical_json(a), ce.canonical_json(b))

    def test_hash_stable_for_same_envelope(self):
        env = ce.make_envelope(
            actor_id="alice",
            document_id="pcb:demo",
            operation="pcb.track.add",
            payload={"layer": "F.Cu", "width": 25000},
            logical_clock=7,
            timestamp_ms=1700000000000,
            nonce="deadbeef",
        )
        self.assertEqual(ce.envelope_hash(env), ce.envelope_hash(env))

    def test_append_jsonl_writes_event(self):
        env = ce.make_envelope(
            actor_id="bob",
            document_id="sch:demo",
            operation="schematic.wire.add",
            payload={"from": [0, 0], "to": [1000, 1000]},
            logical_clock=3,
            timestamp_ms=1700000000123,
            nonce="n1",
        )

        with tempfile.TemporaryDirectory() as td:
            journal = Path(td) / "events.jsonl"
            event_id = ce.append_jsonl(journal, env)
            lines = journal.read_text(encoding="utf-8").splitlines()
            self.assertEqual(len(lines), 1)
            row = json.loads(lines[0])
            self.assertEqual(row["event_id"], event_id)
            self.assertEqual(row["envelope"]["actor_id"], "bob")


if __name__ == "__main__":
    unittest.main()
