# **HW #6**

**Log Parsing & Data Validation System**

In this assignment, you will build a **C++ log parsing and data validation system** using:

- std::regex
- std::regex_match
- std::regex_search
- std::sregex_iterator
- Structured data storage (struct/class)
- File I/O
- Data validation logic

This project simulates real-world cybersecurity and data processing tasks.

**Program Requirements**

Your program must:

- Read input from text files
- Extract structured data using regular expressions
- Validate extracted data
- Generate a formatted report

**Part 1: Log File Parser:**

You are given a server log file in this format:

\[2024 - 01 - 15 14:23 : 45\] INFO User <john@example.com> logged in from 192.168.1.100

\[2024 - 01 - 15 14:24 : 12\] ERROR Failed login attempt for <admin@site.com> from 10.0.90.5

\[2024 - 01 - 15 14:25 : 33\] WARNING Suspicious activity from <hacker@bad.com> at 256.1.1.1

**Extract the Following Fields:**

- Timestamp
- Log level (INFO, ERROR, WARNING)
- Email address (if present)
- IP address
- Full message text

**Your Program Must:**

- Count total log entries
- Count number of:
  - INFO entries
  - ERROR entries
  - WARNING entries
- Extract all email addresses
- Extract all IP addresses
- Validate:
  - Email format
  - IPv4 format

# **Part 2: Contact Information Extractor**

Given a text file containing mixed data, extract:

- Email addresses
- Phone numbers (multiple formats)
- URLs
- Physical addresses (simplified format: City, State ZIP)

Example of address format to match:

Los Angeles, CA 90001

Austin, TX 73301

**You Must:**

- Count how many of each type were found
- Store extracted values in containers
- Avoid duplicate entries (optional extra credit idea)

**Part 3: Data Validation**

For all extracted data:

- Validate each email
- Validate each phone number
- Validate each IP address
- Validate each URL

Your program must:

- Count valid vs invalid entries
- Identify formatting errors
- Display reason for invalid entries

Examples of common issues to detect:

| **Type** | **Example**                     | **Problem**         |
| -------- | ------------------------------- | ------------------- |
| Email    | [admin@.com](mailto:admin@.com) | Missing domain name |
| Email    | user@                           | Missing domain      |
| IP       | 256.1.1.1                       | Octet out of range  |
| IP       | 192.168.1                       | Missing octet       |
| Phone    | 123-4567                        | Missing area code   |

**Part 4: Custom Pattern (Optional)**

Create and implement your own regex pattern for ONE of the following:

- Social media handles (@username)
- Hashtags (#topic)
- Product codes (define your own format)
- License plates (your state format)

You must:

- Define pattern
- Extract matches
- Validate matches
- Demonstrate in program output

**Output Requirements**

Your program must generate a structured report.

//==================SAMPLE OUTPUT=========================

\================================

\== = LOG FILE ANALYSIS ==========

\================================

Total entries : 150

Log Level Summary :

INFO: 120

ERROR : 20

WARNING : 10

\--------------------------------

Email Extraction :

\--------------------------------

Total emails found : 45

Valid : 43

Invalid : 2

Invalid Entries :

<admin@.com> → Invalid domain

user@ → Missing domain

\--------------------------------

IP Address Extraction :

\--------------------------------

Total IPs found : 75

Valid : 72

Invalid : 3

Invalid Entries :

256.1.1.1 → Octet exceeds 255

192.168.1 → Missing octet

10.0.0.999 → Out of range

\================================

\== = CONTACT EXTRACTION ==========

\================================ =

Emails found : 23

Phones found : 18

URLs found : 12

Addresses found : 8

\================================ =

\== = VALIDATION REPORT ========== =

\================================ =

Email Validation :

<user@example.com> ✓

invalid.email ✗(Missing @ symbol)

<test@.com> ✗(Invalid domain)

Phone Validation :

(555) 123 - 4567 ✓ → Standardized : (555) 123 - 4567

555 - 123 - 4567 ✓ → Standardized : (555) 123 - 4567

123 - 4567 ✗(Missing area code)

URL Validation :

<https://example.com> ✓

http: / invalid.com ✗(Invalid protocol format)

\================================

Program Completed Successfully

**The numbers shown in the sample output are examples only.  
Your totals will depend on the contents of your input files.**

If your file only contains:

- 6 emails → program should report 6
- 18 emails → report 18
- 150 emails → report 150

The counts depend entirely on the file content.

**Technical Requirements**

- Must use std::regex
- Must use file input (ifstream)
- Must use structured storage (struct/class or vector)
- Must modularize code (separate functions)
- Must follow proper coding style

# **Common Mistakes to Avoid**

- Using regex_match when regex_search is needed
- Not anchoring patterns with ^ and \$
- Forgetting to validate numeric ranges (e.g., IP octets)
- Not handling malformed log lines
- Hardcoding test data instead of reading from file

Sample text file:

server_log.txt

\[2024 - 01 - 15 08:15 : 22\] INFO User <john@example.com> logged in from 192.168.1.100

\[2024 - 01 - 15 08:17 : 45\] ERROR Failed login attempt for <admin@site.com> from 10.0.0.5

\[2024 - 01 - 15 08:20 : 10\] WARNING Suspicious activity detected for <hacker@bad.com> from 172.16.0.45

\[2024 - 01 - 15 08:25 : 33\] INFO User <mary.jane@company.org> logged in from 192.168.1.101

\[2024 - 01 - 15 08:27 : 01\] ERROR Failed login attempt for user@ from 192.168.1.102

\[2024 - 01 - 15 08:30 : 44\] INFO Password reset requested by <helpdesk@support.net> from 10.1.1.25

\[2024 - 01 - 15 08:35 : 12\] WARNING Multiple failed attempts for <root@server.local> from 256.1.1.1

\[2024 - 01 - 15 08:40 : 55\] INFO User <david_smith@email.co> logged out from 192.168.1.110

\[2024 - 01 - 15 08:45 : 20\] ERROR Account locked for <admin@.com> from 192.168.1

\[2024 - 01 - 15 08:50 : 02\] INFO New user registration : <lisa.white@domain.com> from 172.16.5.23

\[2024 - 01 - 15 08:55 : 18\] WARNING Suspicious IP access from <attacker@malware.net> at 10.0.0.999

\[2024 - 01 - 15 09:00 : 30\] INFO User <michael_brown@tech.io> logged in from 192.168.1.115

\[2024 - 01 - 15 09:05 : 41\] ERROR Database connection failure reported by <dbadmin@company.org> from 10.10.10.10

\[2024 - 01 - 15 09:10 : 22\] INFO Session timeout for <guest@website.com> from 172.16.1.200

\[2024 - 01 - 15 09:15 : 59\] WARNING Invalid login pattern detected for test.user@email from 192.168.1.120

**What This File Contains**

**Valid Emails**

- <john@example.com>
- <admin@site.com>
- <mary.jane@company.org>
- <helpdesk@support.net>
- <david_smith@email.co>
- <lisa.white@domain.com>
- <michael_brown@tech.io>
- <dbadmin@company.org>
- <guest@website.com>
- [attacker@malware.net](mailto:attacker@malware.net)

**Invalid Emails**

- user@
- <admin@.com>
- test.user@email

**Valid IP Addresses**

- 192.168.1.100
- 10.0.0.5
- 172.16.0.45
- 192.168.1.101
- 192.168.1.102
- 10.1.1.25
- 192.168.1.110
- 172.16.5.23
- 192.168.1.115
- 10.10.10.10
- 172.16.1.200
- 192.168.1.120

**Invalid IP Addresses**

- 256.1.1.1 (out of range)
- 192.168.1 (missing octet)
- 10.0.0.999 (out of range)

**Expected Counts**

Total entries: **15**  
Log Levels:

- INFO: 7
- ERROR: 4
- WARNING: 4

Emails found: 15  
Valid: 10  
Invalid: 3  
(Plus 2 edge-case domain formats depending on regex strictness)

IPs found: 15  
Valid: 12  
Invalid: 3