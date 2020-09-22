/*!
 * \file StmtContext.hpp
 *
 * \brief Structs representing the information associated with a statement
 * based on its position in the code and surrounding control structures
 *
 * \author Anna Rift
 * \author Aaron Orenstein
 */

#ifndef SPFIE_STMTCONTEXT_HPP
#define SPFIE_STMTCONTEXT_HPP

#include <memory>
#include <stack>
#include <string>
#include <tuple>
#include <vector>

#include "ArrayAccess.hpp"
#include "ExecSchedule.hpp"
#include "clang/AST/Expr.h"
#include "clang/AST/OperationKinds.h"
#include "clang/AST/Stmt.h"

using namespace clang;

namespace spf_ie {

/*!
 * \struct StmtContext
 *
 * \brief Contains associated information for a statement, such as iteration
 * space and execution schedule.
 */
struct StmtContext {
    StmtContext();

    //! Copy the information from an existing StmtContext.
    //! Preserves only information that builds up in nested contexts,
    //! excluding information that is only applicable per-statement.
    //! \param[in] other Existing StmtContext to copy
    StmtContext(StmtContext* other);

    //! Variables being iterated over
    std::vector<std::string> iterators;
    //! Constraints on iteration -- inequalities and equalities
    std::vector<std::shared_ptr<
        std::tuple<std::string, std::string, BinaryOperatorKind>>>
        constraints;
    //! Execution schedule
    ExecSchedule schedule;
    //! Array positions read from
    std::vector<ArrayAccess> dataReads;
    //! Array positions written to
    std::vector<ArrayAccess> dataWrites;

    //! Get a string representing the iteration space
    std::string getIterSpaceString();

    //! Get a string representing the execution schedule
    std::string getExecScheduleString();

    //! Get a string representing the data reads
    std::string getReadsString();

    //! Get a string representing the data writes
    std::string getWritesString();

    //! Add all the arrays accessed in an expression to the statement's reads
    void processReads(Expr* expr);

    //! Add the arrays accessed in an expression to the statement's writes
    void processWrite(ArraySubscriptExpr* expr);

    // enter* and exit* methods add iterators and constraints when entering a
    // new scope, remove when leaving the scope

    //! Add context information from a for loop
    void enterFor(ForStmt* forStmt);

    //! Remove context information from a for loop
    void exitFor();

    //! Add context information from an if statement
    void enterIf(IfStmt* ifStmt);

    //! Remove context information from an if statement
    void exitIf();

   private:
    //! Convenience function to add a new constraint from the given parameters
    void makeAndInsertConstraint(Expr* lower, Expr* upper,
                                 BinaryOperatorKind oper);

    //! Convenience function to add a new constraint from the given parameters
    void makeAndInsertConstraint(std::string lower, Expr* upper,
                                 BinaryOperatorKind oper);

    //! Get printable string representing the given data accesses
    std::string getDataAccessesString(
        std::vector<ArrayAccess>* accesses);
};

}  // namespace spf_ie

#endif
