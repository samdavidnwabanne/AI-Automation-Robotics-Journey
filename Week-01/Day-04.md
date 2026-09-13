# Day 04 — Prompt Engineering

## What I Worked On

- Practiced structuring effective AI prompts using the **RCTF framework** (Role, Context, Task, Format).
- Explored how giving an AI a clear role, relevant context, a specific task, and an expected output format changes the quality of its responses.
- Built and tested a small **personal prompt library** covering five recurring use cases: research, summarisation, data extraction, content generation, and problem solving.
- Practiced prompt iteration, writing a vague first attempt, testing it, identifying what was missing, and refining it into a stronger version.
- Applied prompting techniques (role prompting, contextual prompting, and format-constrained output) to improve AI-assisted problem solving and communication.

## What I Built

For each use case, I wrote a vague prompt, tested it, then rewrote it using RCTF and re-tested:

| Use case | Example improvement |
|---|---|
| Research | Adding a role + audience turned a generic overview into a decision-ready briefing |
| Summarisation | Locking bullet count + word limit forced prioritisation over paraphrasing |
| Data extraction | Naming exact JSON keys produced consistent, parseable output |
| Content generation | Defining brand voice + audience gave the writing an actual tone instead of generic filler |
| Problem solving | Supplying concrete metrics let the AI diagnose instead of guess |

## Reflection

I explored how the way a prompt is structured directly affects the quality and usefulness of an AI response. The biggest lesson was that **vagueness in, vagueness out** — a short, underspecified prompt almost always produced a generic or unusable answer, while adding role, context, and a defined output format consistently produced sharper, more actionable results. Iteration mattered as much as the initial prompt: the first draft was rarely right, and reading the output to see *what* was missing was the fastest way to improve the next attempt.

## Key Takeaway

> A good prompt isn't about saying more — it's about saying the *right* things: who the AI should be, what it needs to know, what exactly to do, and how the answer should look.
