# Day 6: Advanced Prompt Engineering

## Topic
How modern LLM applications use prompts, context, structured outputs, RAG,
and validation to produce reliable results.

## Key Takeaways
- An LLM receives more than the user's message. Its context can include system
  instructions, conversation history, retrieved information, tool definitions,
  and the current input.
- Advanced prompt engineering means controlling the instructions, context,
  structure, constraints, and expected output.
- **Prompt chaining** splits a complex task into multiple AI steps.
- **Structured output** (e.g. JSON) lets software read specific fields
  without parsing free text.
- **RAG** supplies relevant external information to the model. It does not
  require an AI agent.
- Reliable systems need testing, validation, good context, and clear
  handling of failure cases.

## Project: University Policy Helpdesk Assistant
**Problem:** Students struggle to find answers in long policy documents, and
staff spend time repeating the same answers.

**Workflow:**
1. Classify the question and flag sensitive topics (LLM, JSON output)
2. Retrieve the top 4 relevant policy passages (RAG)
3. Draft an answer using only the retrieved passages (LLM, JSON output)
4. Validate the schema, the citation, and that the quote is grounded in the source
5. Return the answer with its source, or escalate to a human

## Technique Fit
| Technique | Used? | Why |
|---|---|---|
| Prompt chaining | Yes | Separate steps are easier to test and debug |
| Task decomposition | Yes | Triage, retrieve, draft, verify |
| Structured output | Yes | Enables validation and citation display |
| RAG | Yes | Policies change, and answers need sources |
| AI agent | No | The task is predictable, so a fixed workflow is safer and cheaper |

## Failure Points and Safeguards
1. **Wrong or outdated retrieval:** effective dates, similarity threshold,
   retrieval testing
2. **Hallucination:** "answerable: false" option, verbatim quote check, low
   temperature
3. **Sensitive questions:** routed to human staff, keyword backup rules,
   weekly sample review

## Reflection
A reliable LLM app is a designed system, not one clever prompt. Each
component (instructions, retrieval, structure, validation, human review)
covers a weakness of the model.

## Files
- `report.md`: full report with prompts and workflow diagram
