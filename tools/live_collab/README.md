# Live Collaboration Milestone 1 (M1)

This folder contains the first concrete foundation for the KiCad live-collaboration fork:

- a deterministic **change envelope** format,
- canonical JSON serialization,
- stable SHA-256 event IDs,
- and a tiny append-only JSONL journal writer.

## Why this first

Before transport/UI work, collaborators need a deterministic event format so all peers can:

1. hash the same event to the same ID,
2. deduplicate/replay safely,
3. and keep merge/reconciliation logic predictable.

## Quick usage

```bash
python3 tools/live_collab/change_envelope.py \
  --actor demo-user \
  --document pcb:demo-board \
  --op pcb.track.add \
  --payload '{"layer":"F.Cu","start":[100000,200000],"end":[300000,400000],"width":25000}'
```

## Run tests

```bash
python3 -m unittest tools.live_collab.test_change_envelope
```
