# KiCad Live Collaboration — Architecture (Milestone 1)

## Status
- **Milestone:** M1 (fork + architecture + scaffolding)
- **Date:** 2026-04-15
- **Branch:** `feature/live-collab-m1`

## Product target
Deliver native real-time collaboration in KiCad with:
1. **Presentation polish** inspired by Google Slides (presence + smooth co-edit awareness).
2. **Developer workflow confidence** inspired by VS Code Live Share (clear host/guest roles, fast join flow, low friction reconnect).
3. **Self-host and managed server support** with explicit **remote connection + password auth** paths.

## Non-goals for M1
- No production wire protocol lock.
- No editor conflict resolver shipping path yet.
- No final UX strings/assets.

## System architecture (planned)

### 1) Collaboration Core (client-side, in-process)
`kicommon` collaboration layer provides:
- Session state machine (idle/hosting/joining/connected/degraded).
- Transport abstraction (WebSocket first, adaptable later).
- Auth abstraction (password mode now, provider/token mode next).
- Presence model (participants, cursor focus, activity state).

### 2) Collaboration Gateway (server-side, external)
Stateless-ish hub process (future repo/module) handling:
- Room lifecycle (create/join/leave).
- Password challenge/verification.
- Event fan-out and sequencing.
- Optional persistence hooks.

### 3) Domain adapters (KiCad tools)
Tool-specific adapters translate local editor operations into collaboration events and apply remote events back into tool models.

## Connection/auth model (M1 direction)
- `host_url` + `room_id` + `display_name` + `password`.
- Password is treated as **secret** and never logged.
- Token slot kept in config for future OAuth/provider exchange.
- Reconnect strategy: bounded retries + backoff + user-visible status.

## UX polish targets (guidance)
- **Google Slides cues:** avatar chips, “currently editing” affordances, soft cursor trails.
- **VS Code Live Share cues:** explicit “Start Session / Join Session”, sharable invite metadata, host controls.
- Zero modal spam; status should live in persistent collaboration panel.

## Milestone breakdown

### M1 (this change)
- Fork working branch established.
- Architecture doc established.
- Collaboration scaffolding interfaces + stubs added behind build flag.
- Deterministic collaboration event-envelope tooling added (`tools/live_collab`).

### M2
- Implement basic gateway protocol and connect/disconnect flow.
- Session panel in UI shell with join/create.

### M3
- First synchronized object path (schematic selection + viewport presence).
- Password handshake end-to-end.

### M4
- Broader edit syncing + conflict controls.
- Performance hardening and telemetry.

## Acceptance criteria for this milestone
- Build remains unaffected by default (feature gate OFF).
- New collaboration interfaces compile when enabled.
- Clear follow-on path for remote+password flow.

## Validation plan (forward)
When runnable end-to-end, perform:
1. Local macOS install.
2. Real interaction checks via Mac MCP/local macOS control.
3. Host + guest join, password auth, reconnect, and presence smoke test.
