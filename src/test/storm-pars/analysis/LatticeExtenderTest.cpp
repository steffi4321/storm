//
// Created by Jip Spel on 20.09.18.
//

// TODO: cleanup includes
#include "gtest/gtest.h"
#include "storm-config.h"
#include "test/storm_gtest.h"

#include "storm-parsers/parser/FormulaParser.h"
#include "storm/logic/Formulas.h"
#include "storm/models/sparse/StandardRewardModel.h"
#include "storm/modelchecker/prctl/SparseDtmcPrctlModelChecker.h"
#include "storm/modelchecker/results/ExplicitQuantitativeCheckResult.h"
#include "storm-parsers/parser/AutoParser.h"
#include "storm-parsers/parser/PrismParser.h"
#include "storm/storage/expressions/ExpressionManager.h"
#include "storm/api/builder.h"

#include "storm-pars/analysis/Lattice.h"
#include "storm-pars/analysis/LatticeExtender.h"
#include "storm-pars/transformer/SparseParametricDtmcSimplifier.h"

#include "storm-pars/api/storm-pars.h"
#include "storm/api/storm.h"

#include "storm-parsers/api/storm-parsers.h"

TEST(LatticeExtenderTest, Brp_with_bisimulation) {
    std::string programFile = STORM_TEST_RESOURCES_DIR "/pdtmc/brp16_2.pm";
    std::string formulaAsString = "P=? [F s=4 & i=N ]";
    std::string constantsAsString = ""; //e.g. pL=0.9,TOACK=0.5

    // Program and formula
    storm::prism::Program program = storm::api::parseProgram(programFile);
    program = storm::utility::prism::preprocess(program, constantsAsString);
    std::vector<std::shared_ptr<const storm::logic::Formula>> formulas = storm::api::extractFormulasFromProperties(storm::api::parsePropertiesForPrismProgram(formulaAsString, program));
    std::shared_ptr<storm::models::sparse::Dtmc<storm::RationalFunction>> model = storm::api::buildSparseModel<storm::RationalFunction>(program, formulas)->as<storm::models::sparse::Dtmc<storm::RationalFunction>>();
    std::shared_ptr<storm::models::sparse::Dtmc<storm::RationalFunction>> dtmc = model->as<storm::models::sparse::Dtmc<storm::RationalFunction>>();
    auto simplifier = storm::transformer::SparseParametricDtmcSimplifier<storm::models::sparse::Dtmc<storm::RationalFunction>>(*dtmc);
    ASSERT_TRUE(simplifier.simplify(*(formulas[0])));
    model = simplifier.getSimplifiedModel();

    // Apply bisimulation
    storm::storage::BisimulationType bisimType = storm::storage::BisimulationType::Strong;
    if (storm::settings::getModule<storm::settings::modules::BisimulationSettings>().isWeakBisimulationSet()) {
        bisimType = storm::storage::BisimulationType::Weak;
    }

    dtmc = storm::api::performBisimulationMinimization<storm::RationalFunction>(model, formulas, bisimType)->as<storm::models::sparse::Dtmc<storm::RationalFunction>>();

    ASSERT_EQ(dtmc->getNumberOfStates(), 99ull);
    ASSERT_EQ(dtmc->getNumberOfTransitions(), 195ull);

    auto *extender = new storm::analysis::LatticeExtender<storm::RationalFunction>(dtmc);
    auto criticalTuple = extender->toLattice(formulas);
    EXPECT_EQ(dtmc->getNumberOfStates(), std::get<1>(criticalTuple));
    EXPECT_EQ(dtmc->getNumberOfStates(), std::get<2>(criticalTuple));

    auto lattice = std::get<0>(criticalTuple);
    for (auto i = 0; i < dtmc->getNumberOfStates(); ++i) {
        EXPECT_TRUE(lattice->getAddedStates()[i]);
    }

    // Check on some nodes
    EXPECT_EQ(storm::analysis::Lattice::ABOVE, lattice->compare(1,0));
    EXPECT_EQ(storm::analysis::Lattice::ABOVE, lattice->compare(1,5));
    EXPECT_EQ(storm::analysis::Lattice::ABOVE, lattice->compare(5,0));
    EXPECT_EQ(storm::analysis::Lattice::ABOVE, lattice->compare(94,5));
    EXPECT_EQ(storm::analysis::Lattice::UNKNOWN, lattice->compare(7,13));
}

TEST(LatticeExtenderTest, Brp_without_bisimulation) {
    std::string programFile = STORM_TEST_RESOURCES_DIR "/pdtmc/brp16_2.pm";
    std::string formulaAsString = "P=? [F s=4 & i=N ]";
    std::string constantsAsString = ""; //e.g. pL=0.9,TOACK=0.5

    // Program and formula
    storm::prism::Program program = storm::api::parseProgram(programFile);
    program = storm::utility::prism::preprocess(program, constantsAsString);
    std::vector<std::shared_ptr<const storm::logic::Formula>> formulas = storm::api::extractFormulasFromProperties(storm::api::parsePropertiesForPrismProgram(formulaAsString, program));
    std::shared_ptr<storm::models::sparse::Dtmc<storm::RationalFunction>> model = storm::api::buildSparseModel<storm::RationalFunction>(program, formulas)->as<storm::models::sparse::Dtmc<storm::RationalFunction>>();
    std::shared_ptr<storm::models::sparse::Dtmc<storm::RationalFunction>> dtmc = model->as<storm::models::sparse::Dtmc<storm::RationalFunction>>();
    auto simplifier = storm::transformer::SparseParametricDtmcSimplifier<storm::models::sparse::Dtmc<storm::RationalFunction>>(*dtmc);
    ASSERT_TRUE(simplifier.simplify(*(formulas[0])));
    model = simplifier.getSimplifiedModel();
    dtmc = model->as<storm::models::sparse::Dtmc<storm::RationalFunction>>();

    ASSERT_EQ(dtmc->getNumberOfStates(), 193ull);
    ASSERT_EQ(dtmc->getNumberOfTransitions(), 383ull);

    auto *extender = new storm::analysis::LatticeExtender<storm::RationalFunction>(dtmc);
    auto criticalTuple = extender->toLattice(formulas);
    EXPECT_EQ(183, std::get<1>(criticalTuple));
    EXPECT_EQ(186, std::get<2>(criticalTuple));
}


