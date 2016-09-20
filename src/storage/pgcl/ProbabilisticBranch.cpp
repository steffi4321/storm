#include "src/storage/pgcl/ProbabilisticBranch.h"
#include "src/storage/pgcl/AbstractStatementVisitor.h"

namespace storm {
    namespace pgcl {
        ProbabilisticBranch::ProbabilisticBranch(storm::expressions::Expression const& probability, std::shared_ptr<storm::pgcl::PgclBlock> const& left, std::shared_ptr<storm::pgcl::PgclBlock> const& right) :
        probability(probability) {
            rightBranch = right;
            leftBranch = left;
        }
        
        storm::expressions::Expression const& ProbabilisticBranch::getProbability() const {
            return this->probability;
        }

        void ProbabilisticBranch::accept(storm::pgcl::AbstractStatementVisitor& visitor) {
            visitor.visit(*this);
        }
    }
}

