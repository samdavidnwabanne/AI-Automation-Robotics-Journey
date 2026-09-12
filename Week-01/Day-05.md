# Day 05 — First AI Automation

## What I Worked On

- Built my first practical AI automation workflow using **n8n**, combining a form trigger, an AI processing step, and an output action.
- Explored how a workflow can receive user input, send it to an AI model, process it, and produce a structured, organised output automatically.
- Built a **feedback summarizer**: a Google-style form collects a participant's name and feedback, an AI model (Google Gemini) analyses it, and the result is saved to Google Sheets.
- Learned how to write a structured AI prompt (Role → Context → Task → Format) and pass the user's feedback into it dynamically using n8n's variable syntax.
- Tested the workflow end-to-end with multiple real inputs to check how reliably it handled variation, and used what I found to improve the workflow's error handling.

## Overview

This is my first practical AI automation workflow, built with n8n. The workflow receives user feedback, sends it to an AI model for processing and summarisation, and saves the original feedback along with the AI-generated summary to Google Sheets — turning unstructured, free-text feedback into a consistent, reviewable format with no manual data entry.

## Workflow

 User Input → AI Process → Output
 Google Form → n8n → AI Model (Gemini) → Summary → Google Sheets


## How It Works

1. Receive the user's form submission (name + feedback).
2. Extract the user's name and feedback from the trigger data.
3. Send the feedback to the AI model as part of a structured prompt.
4. The prompt instructs the AI to act as a "Feedback Analysis Assistant" and extract two things: the main positive point and the main area for improvement.
5. Insert the user's feedback dynamically into the prompt using n8n's `{{ }}` variable syntax.
6. Receive the AI-generated response in a fixed, predictable format.
7. Append the original feedback and the AI-generated summary as a new row in Google Sheets, along with the name and timestamp.

## Testing with Edge Cases

I tested the workflow with several different inputs to see how well it handled variation, not just "clean" test data:

- **Normal feedback** — processed correctly; the AI extracted a clear positive point and improvement point.
- **Very long feedback** — the AI condensed a lengthy paragraph into the required one-sentence fields without losing the main point.
- **Feedback in another language (French)** — handled correctly, with output still returned in the expected format.
- **Nonsense / meaningless feedback** — this exposed a real issue. Instead of failing gracefully, the AI step hung and never completed. I traced this to the workflow having no timeout or retry limit set, so a problematic input just stalled the entire execution.
- **Empty form submission** — I discovered the form field is set as required, which blocks empty submissions before they even reach the workflow, meaning I couldn't fully test this case as-is.

**Fixes identified:** add a request timeout and a capped retry limit on the AI step, and enable "Continue on Fail" so a problematic submission still gets logged rather than freezing the whole workflow.

## Screenshots

### 1. Trigger / Input

The workflow receives the user's name and feedback through the form submission.

![Trigger/Input](AI-Automation-Trigger.png)

### 2. AI Processing

The user's feedback is passed into the AI step, where the prompt instructs the model to process and summarise it.

![AI Processing](AI-Automation-AI-Processing.png)

### 3. Final Output

The original feedback and AI-generated summary are saved to Google Sheets.

![Final Output](AI-Automation-Output.png)

## Key Concepts

- Workflow automation
- AI integration
- Triggers and actions
- Dynamic data
- Prompt engineering (RCTF: Role, Context, Task, Format)
- AI-generated output
- Google Sheets integration
- Error handling and edge-case testing

## Reflection

Today I moved from learning about AI and automation separately to combining them into one practical, working system. Building the workflow helped me understand how a well-structured prompt directly determines the quality and consistency of the AI's output — and testing it with edge cases (long input, another language, nonsense text, empty submissions) taught me that a good automation isn't just one that works on clean data, but one that fails safely when it doesn't. This project gave me a much clearer picture of how AI can be embedded into automated processes to turn raw, unstructured input into useful, structured output with minimal manual effort.
