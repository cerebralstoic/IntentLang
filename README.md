# IntentLang

*A Correctness-Aware Compiler for Algorithmic and Decision-Based Intent*

---

![Language](https://img.shields.io/badge/Language-C++-blue)
![Compiler](https://img.shields.io/badge/Project-Compiler%20Design-success)
![DSL](https://img.shields.io/badge/Type-Domain%20Specific%20Language-orange)
![Target](https://img.shields.io/badge/Target-C-lightgrey)
![Status](https://img.shields.io/badge/Status-Working-brightgreen)
![NLP](https://img.shields.io/badge/Feature-Rule--Based%20NLP-purple)

## 📌 Overview

**IntentLang** is a domain-specific language (DSL) and compiler designed to translate **high-level intent specifications and natural language rules** into **verified executable C code**.

Unlike traditional code generators, IntentLang focuses on:

* **Intent expression instead of syntax-heavy programming**
* **Semantic correctness validation before code generation**
* **Rule-based NLP conversion (Natural Language → DSL)**
* **Formal compiler construction principles**

The project implements a **complete compiler pipeline**, covering all core phases of **Compiler Design**, and is extensible toward **algorithmic reasoning and verification**.

---

## 🎯 Motivation

Most beginner compilers focus only on syntax translation. IntentLang goes a step further by:

* Validating **semantic correctness**
* Enforcing **logical constraints**
* Rejecting incorrect intent specifications
* Supporting **natural language input via NLP**
* Generating **deterministic and verifiable C programs**

This makes IntentLang suitable for:

* Decision-based systems
* Rule engines
* Algorithmic intent validation
* Educational demonstrations of compiler theory

---

## 🧩 Language Philosophy

IntentLang allows users to express **what they want to achieve**, not *how to write code*.

Example (Natural Language Input):

```text
Marks between 0 and 100
If marks less than 40 then fail
If marks greater than 85 then assign grade A
If marks greater than 70 then assign grade B
Otherwise assign grade C
```

Converted DSL:

```intent
marks range 0 to 100
fail if marks < 40
grade A if marks > 85
grade B if marks > 70
grade C otherwise
```

The compiler verifies the logic and generates equivalent **C code**.

---

## 🏗️ Compiler Architecture

IntentLang follows a **classic compiler architecture with NLP integration**:

```text
Natural Language Input
        ↓
Rule-Based NLP
        ↓
IntentLang DSL
        ↓
Lexical Analysis
        ↓
Syntax Analysis (LL(1) Recursive Descent Parser)
        ↓
Abstract Syntax Tree (AST)
        ↓
Semantic Analysis (Correctness Validation)
        ↓
Intermediate Representation (TAC)
        ↓
Target Code Generation (C)
```

---

## ▶️ How to Build & Run

Compile

```bash
g++ main.cpp lexer/Lexer.cpp parser/Parser.cpp semantic/SemanticAnalyzer.cpp ir/IRGenerator.cpp codegen/CGenerator.cpp nlp/NLPProcessor.cpp -o intentlang
```

Run Compiler

```bash
./intentlang
```

Compile Generated C Code

```bash
gcc output.c -o program
./program
```
