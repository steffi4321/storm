#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include "../logic/Formulas.h"


#include "helpers.h"
#include "boostPyExtension.h"



BOOST_PYTHON_MODULE(_logic)
{
    using namespace boost::python;

    ////////////////////////////////////////////
    // Formula
    ////////////////////////////////////////////
    defineClass<storm::logic::Formula, void, boost::noncopyable>("Formula",
    "Generic Storm Formula")
        .def("__str__", &storm::logic::Formula::toString)
    ;

    //
    // Path Formulae
    //
    defineClass<storm::logic::PathFormula, storm::logic::Formula, boost::noncopyable>("PathFormula",
    "Formula about the probability of a set of paths in an automaton");
    defineClass<storm::logic::UnaryPathFormula, storm::logic::PathFormula, boost::noncopyable>("UnaryPathFormula",
    "Path formula with one operand");
    defineClass<storm::logic::EventuallyFormula, storm::logic::UnaryPathFormula>("EventuallyFormula",
    "Formula for eventually");
    defineClass<storm::logic::GloballyFormula, storm::logic::UnaryPathFormula>("GloballyFormula",
    "Formula for globally");
    defineClass<storm::logic::BinaryPathFormula, storm::logic::PathFormula, boost::noncopyable>("BinaryPathFormula",
    "Path formula with two operands");
    defineClass<storm::logic::BoundedUntilFormula, storm::logic::BinaryPathFormula, boost::noncopyable>("BoundedUntilFormula",
    "Until Formula with either a step or a time bound.");
    defineClass<storm::logic::ConditionalPathFormula, storm::logic::BinaryPathFormula>("ConditionalPathFormula",
    "Path Formula with the right hand side being a condition.");
    defineClass<storm::logic::UntilFormula, storm::logic::BinaryPathFormula>("UntilFormula",
    "Path Formula for unbounded until");


    //
    // Reward Path Formulae
    //
    defineClass<storm::logic::RewardPathFormula, storm::logic::Formula, boost::noncopyable>("RewardPathFormula",
    "Formula about the rewards of a set of paths in an automaton");
    defineClass<storm::logic::CumulativeRewardFormula, storm::logic::RewardPathFormula>("CumulativeRewardFormula",
    "Summed rewards over a the paths");
    defineClass<storm::logic::InstantaneousRewardFormula, storm::logic::RewardPathFormula>("InstanteneousRewardFormula",
    "");
    defineClass<storm::logic::LongRunAverageRewardFormula, storm::logic::RewardPathFormula>("LongRunAverageRewardFormula",
    "");
    defineClass<storm::logic::ReachabilityRewardFormula, storm::logic::RewardPathFormula>("ReachabilityRewardFormula",
    "");


    //
    // State Formulae
    //
    defineClass<storm::logic::StateFormula, storm::logic::Formula, boost::noncopyable>("StateFormula",
    "Formula about a state of an automaton");
    defineClass<storm::logic::AtomicExpressionFormula, storm::logic::StateFormula>("AtomicExpressionFormula",
    "");
    defineClass<storm::logic::AtomicLabelFormula, storm::logic::StateFormula>("AtomicLabelFormula",
    "");
    defineClass<storm::logic::BooleanLiteralFormula, storm::logic::StateFormula>("BooleanLiteralFormula",
    "");
    defineClass<storm::logic::UnaryStateFormula, storm::logic::StateFormula, boost::noncopyable>("UnaryStateFormula",
    "State formula with one operand");
    defineClass<storm::logic::UnaryBooleanStateFormula, storm::logic::UnaryStateFormula>("UnaryBooleanStateFormula",
    "");
    defineClass<storm::logic::OperatorFormula, storm::logic::UnaryStateFormula, boost::noncopyable>("OperatorFormula",
    "");
    defineClass<storm::logic::ExpectedTimeOperatorFormula, storm::logic::OperatorFormula>("ExpectedTimeOperator",
    "The expected time between two events");
    defineClass<storm::logic::LongRunAverageOperatorFormula, storm::logic::OperatorFormula>("LongRunAvarageOperator",
    "");
    defineClass<storm::logic::ProbabilityOperatorFormula, storm::logic::OperatorFormula>("ProbabilityOperator",
    "");
    defineClass<storm::logic::RewardOperatorFormula, storm::logic::OperatorFormula>("RewardOperatorFormula",
    "");
    defineClass<storm::logic::BinaryStateFormula, storm::logic::StateFormula, boost::noncopyable>("BinaryStateFormula",
    "State formula with two operands");
    defineClass<storm::logic::BinaryBooleanStateFormula, storm::logic::BinaryStateFormula>("BooleanBinaryStateFormula",
    "");

}
