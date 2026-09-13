# Day 03 — Introduction to Automation

## What I Worked On

Today I explored the basics of automation and how it can be used to reduce repetitive manual work.

I learned about the TAO model:

- **T — Trigger:** What starts the automation
- **A — Action:** What the automation does
- **O — Output:** The final result

I also explored workflows, flowcharts, APIs and tools such as n8n, Zapier and Make.

## Manual Process I Chose

For my automation task, I looked at a simple customer feedback process.

As a business owner, after a customer purchases and uses a product, I would like to receive their feedback and thank them for taking the time to share it.

Normally, I would have to check the feedback submitted by each customer and manually send a thank-you email. When there are many customers, doing this repeatedly can become time-consuming.

### Current Manual Process

Customer purchases product  
→ Customer submits feedback  
→ I receive the feedback  
→ I check the customer's email  
→ I write a thank-you message  
→ I send the email

## Automated Workflow

I redesigned the process so that the thank-you email is sent automatically after the customer submits their feedback.

### TAO

**Trigger:** Customer submits the feedback form.

**Action:** n8n receives the submission and sends a personalised thank-you email.

**Output:** The customer receives the thank-you email.

### Automated Process

Customer submits feedback form  
→ n8n receives the submission  
→ n8n sends a personalised thank-you email  
→ Customer receives the email

## Tool Used

I used **n8n** to build and test the automation.

I chose n8n because it allows different tools and services to be connected in a workflow without having to manually perform each step. I had also already used n8n during the programme, so I was familiar with how its workflows work.

## What I Built

I implemented a simple version of the workflow using an **n8n Form Trigger** and **Gmail**.

The form collects:

- Customer name
- Customer email
- Customer feedback

Once the form is submitted, the information is passed to the Gmail node, which automatically sends a thank-you email to the customer.

For testing, I submitted feedback such as:

> "The products we bought from you were received in good conditions and are serving us well."

The workflow successfully sent and delivered the thank-you email.

## Workflow Diagram

I also created a simple flowchart using draw.io to visually represent the automated process.

The diagram shows the flow from the customer's feedback submission through the automated email process to the final result.

## Visual Evidence

### 1. n8n Workflow Canvas

![n8n Workflow Canvas](../../Images/Day-03-Workflow-Canvas.png)

### 2. Feedback Form

![Feedback Form](../../Images/Day-03-Feedback-Form.png)

### 3. Gmail Configuration

![Gmail Configuration](../../Images/Day-03-Gmail-Configuration.png)

### 4. Email Notification

![Email Notification](../../Images/Day-03-Email-Notification.png)

### 5. Received Email

![Received Email](../../Images/Day-03-Received-Email.png)

### 6. Workflow Diagram

![Workflow Diagram](../../Images/Day-03-Workflow-Diagram.png)

## Key Takeaway

Today helped me understand automation more practically. I learned how a repetitive manual task can be broken down into a trigger, action and output, and then connected into a workflow that reduces the need for manual work.

## Reflection

Building and testing the workflow helped me see how automation can be applied to simple real-world processes. It was also useful to see the difference between understanding automation theoretically and actually building and testing a workflow.
