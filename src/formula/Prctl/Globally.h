/*
 * Next.h
 *
 *  Created on: 26.12.2012
 *      Author: Christian Dehnert
 */

#ifndef STORM_FORMULA_PRCTL_GLOBALLY_H_
#define STORM_FORMULA_PRCTL_GLOBALLY_H_

#include "src/formula/abstract/Globally.h"
#include "AbstractPathFormula.h"
#include "AbstractStateFormula.h"
#include "src/formula/AbstractFormulaChecker.h"
#include "src/modelchecker/ForwardDeclarations.h"

namespace storm {
namespace formula {
namespace prctl {

template <class T> class Globally;

/*!
 *  @brief Interface class for model checkers that support Globally.
 *   
 *  All model checkers that support the formula class Globally must inherit
 *  this pure virtual class.
 */
template <class T>
class IGloballyModelChecker {
    public:
		/*!
         *  @brief Evaluates Globally formula within a model checker.
         *
         *  @param obj Formula object with subformulas.
         *  @return Result of the formula for every node.
         */
        virtual std::vector<T>* checkGlobally(const Globally<T>& obj, bool qualitative) const = 0;
};

/*!
 * @brief
 * Class for a Abstract (path) formula tree with a Globally node as root.
 *
 * Has one Abstract state formula as sub formula/tree.
 *
 * @par Semantics
 * The formula holds iff globally \e child holds.
 *
 * The subtree is seen as part of the object and deleted with the object
 * (this behavior can be prevented by setting them to nullptr before deletion)
 *
 * @see AbstractPathFormula
 * @see AbstractFormula
 */
template <class T>
class Globally : public storm::formula::abstract::Globally<T, AbstractStateFormula<T>>,
					  public AbstractPathFormula<T> {

public:
	/*!
	 * Empty constructor
	 */
	Globally() {
		//intentionally left empty
	}

	/*!
	 * Constructor
	 *
	 * @param child The child node
	 */
	Globally(AbstractStateFormula<T>* child)
		: storm::formula::abstract::Globally<T, AbstractStateFormula<T>>(child) {
		//intentionally left empty
	}

	/*!
	 * Constructor.
	 *
	 * Also deletes the subtree.
	 * (this behaviour can be prevented by setting the subtrees to nullptr before deletion)
	 */
	virtual ~Globally() {
	  //intentionally left empty
	}


	/*!
	 * Clones the called object.
	 *
	 * Performs a "deep copy", i.e. the subtrees of the new object are clones of the original ones
	 *
	 * @returns a new Globally-object that is identical the called object.
	 */
	virtual AbstractPathFormula<T>* clone() const {
		Next<T>* result = new Next<T>();
		if (child != nullptr) {
			result->setChild(child);
		}
		return result;
	}

	/*!
	 * Calls the model checker to check this formula.
	 * Needed to infer the correct type of formula class.
	 *
	 * @note This function should only be called in a generic check function of a model checker class. For other uses,
	 *       the methods of the model checker should be used.
	 *
	 * @returns A vector indicating the probability that the formula holds for each state.
	 */
	virtual std::vector<T> *check(const storm::modelchecker::AbstractModelChecker<T>& modelChecker, bool qualitative) const {
		return modelChecker.template as<IGloballyModelChecker>()->checkGlobally(*this, qualitative);
	}
	
	/*!
     *  @brief Checks if the subtree conforms to some logic.
     * 
     *  @param checker Formula checker object.
     *  @return true iff the subtree conforms to some logic.
     */
	virtual bool conforms(const AbstractFormulaChecker<T>& checker) const {
		return checker.conforms(this->child);
	}
};

} //namespace prctl
} //namespace formula
} //namespace storm

#endif /* STORM_FORMULA_PRCTL_GLOBALLY_H_ */
