#ifndef SPFIE_UTILS_HPP
#define SPFIE_UTILS_HPP

#include <map>
#include <string>

#include "clang/AST/Expr.h"
#include "clang/AST/OperationKinds.h"
#include "clang/AST/Stmt.h"

//! Base name (will be followed by a unique string) for use in variable
//! substitutions
#define REPLACEMENT_VAR_BASE_NAME "_rVar"

using namespace clang;

namespace spf_ie {

/*!
 * \class Utils
 *
 * \brief A helper class with various methods for string conversion.
 */
class Utils {
public:
  Utils() = delete;

  //! Print an error to standard error and exit with error status
  static void printErrorAndExit(std::string message);

  //! Print an error to standard error, including the context of a
  //! statement in the source code, and exit with error status
  static void printErrorAndExit(std::string message, clang::Stmt *stmt);

  //! Print a line (horizontal separator) to standard output
  static void printSmallLine();

  //! Get the source code of a statement as a string
  static std::string stmtToString(clang::Stmt *stmt);

  //! Retrieve "all" array accesses, from left to right, contained in an
  //! expression.
  //! Recurses into BinaryOperators.
  //! \param[in] expr Expression to process
  //! \param[out] currentList List of accesses
  static void getExprArrayAccesses(
      Expr *expr, std::vector<ArraySubscriptExpr *> &currentList);

  //! Get a unique variable name to use in substitutions
  static std::string getVarReplacementName();

  //! Get a string representation of a binary operator
  static std::string binaryOperatorKindToString(BinaryOperatorKind bo);

  //! Check whether the provided expression is a variable or numeric literal (as opposed to neither of the two)
  //! \param[in] expr Expression to check
  //! \return True iff the expression is a variable or numeric literal
  static bool isVarOrNumericLiteral(const Expr *expr);

private:
  //! String representations of valid operators for use in constraints
  static const std::map<BinaryOperatorKind, std::string> operatorStrings;

  //! Number to be used (and incremented) when creating replacement variable
  //! names
  static unsigned int replacementVarNumber;
};

}  // namespace spf_ie

#endif
