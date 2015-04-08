#ifndef STORM_LOGIC_INSTANTANEOUSREWARDFORMULA_H_
#define STORM_LOGIC_INSTANTANEOUSREWARDFORMULA_H_

#include <boost/variant.hpp>

#include "src/logic/RewardPathFormula.h"

namespace storm {
    namespace logic {
        class InstantaneousRewardFormula : public RewardPathFormula {
        public:
            InstantaneousRewardFormula(uint_fast64_t timeBound);
            
            InstantaneousRewardFormula(double timeBound);
            
            virtual ~InstantaneousRewardFormula() {
                // Intentionally left empty.
            }
            
            virtual bool isInstantaneousRewardFormula() const override;
            
            virtual std::ostream& writeToStream(std::ostream& out) const override;
            
            bool hasDiscreteTimeBound() const;
            
            uint_fast64_t getDiscreteTimeBound() const;

            bool hasContinuousTimeBound() const;
            
            double getContinuousTimeBound() const;
            
        private:
            boost::variant<uint_fast64_t, double> timeBound;
        };
    }
}

#endif /* STORM_LOGIC_INSTANTANEOUSREWARDFORMULA_H_ */