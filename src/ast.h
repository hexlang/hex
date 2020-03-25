/*
 * Copyright (c) 2020 Chris Watson <cawatson1993@gmail.com>
 * Author: Chris Watson <cawatson1993@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include <memory>

/**
 * This virtual class represents one of any potential nodes in our AST.
 * All other AST types should inherit from this.
 */
class ASTNode {
 public:
  virtual ~ASTNode() {}
  virtual const char *class_name() const = 0;

 protected:
  ASTNode() {}
};

/**
 * Represents a program
 */
class Program : public ASTNode {
 public:
  Program() {}
  uint64_t body_size;
  std::shared_ptr<ASTNode *> body;

 private:
  virtual const char *class_name() const override { return "Program"; }
};

class Expression : public ASTNode {};
