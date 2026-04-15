# Collaboration scaffolding (experimental)

This directory contains Milestone 1 scaffolding for live collaboration.

Enabled only with:

```bash
-DKICAD_EXPERIMENTAL_COLLAB=ON
```

Current scope:
- High-level `LIVE_COLLAB_CLIENT` state machine shell
- Session state/manager scaffold
- Password auth provider scaffold
- Stub transport for early integration tests

No production protocol is implemented yet.
