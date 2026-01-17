# IntentLang  
*A Correctness-Aware Compiler for Algorithmic and Decision-Based Intent*

---
![Language](https://img.shields.io/badge/Language-C++-blue)
![Compiler](https://img.shields.io/badge/Project-Compiler%20Design-success)
![DSL](https://img.shields.io/badge/Type-Domain%20Specific%20Language-orange)
![Target](https://img.shields.io/badge/Target-C-lightgrey)
![Status](https://img.shields.io/badge/Status-Working-brightgreen)
## 📌 Overview

**IntentLang** is a domain-specific language (DSL) and compiler designed to translate **high-level intent specifications** into **verified executable C code**.

Unlike traditional code generators, IntentLang focuses on:
- **Intent expression instead of syntax-heavy programming**
- **Semantic correctness validation before code generation**
- **Formal compiler construction principles**

The project implements a **complete compiler pipeline**, covering all core phases of **Compiler Design**, and is extensible toward **algorithmic reasoning and verification**.

---

## 🎯 Motivation

Most beginner compilers focus only on syntax translation. IntentLang goes a step further by:

- Validating **semantic correctness**
- Enforcing **logical constraints**
- Rejecting incorrect intent specifications
- Generating **deterministic and verifiable C programs**

This makes IntentLang suitable for:
- Decision-based systems
- Rule engines
- Algorithmic intent validation
- Educational demonstrations of compiler theory

---

## 🧩 Language Philosophy

IntentLang allows users to express **what they want to achieve**, not *how to write code*.

Example intent:

```intent
goal: grade_evaluator

input:
    marks

constraints:
    marks range 0 to 100
    fail if marks < 40
    grade A if marks >= 85
    grade B if marks >= 70
    grade C otherwise

output:
    grade
```
The compiler verifies the logic and generates equivalent **C code**.

---

## 🏗️ Compiler Architecture

IntentLang follows a **classic compiler architecture**:

```text
IntentLang Source
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
## ▶️ How to Build & Run
Compile
```Bash
g++ main.cpp lexer/Lexer.cpp parser/Parser.cpp semantic/SemanticAnalyzer.cpp ir/IRGenerator.cpp codegen/CGenerator.cpp -o intentlang
```
Run Compiler
```Bash
./intentlang
```
Compile Generated C Code
```Bash
gcc output.c -o program
./program
```
