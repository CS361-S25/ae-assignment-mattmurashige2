#include "Org.h"
#include "emp/math/Random.hpp"
#include "emp/tools/string_utils.hpp"

#ifndef COYOTE_H
#define COYOTE_H

class Coyote : public Organism {

    public:
    Coyote(emp::Ptr<emp::Random> _random, double _points=0.0, std::string _color="grey") :
        Organism(_random, _points, _color) {;}

    /**
     * @brief Gets the type identifier of the organism.
     *
     * This function returns a string representation of the organism's type.
     *
     * @return std::string "Coyote"
     */
    std::string GetType() {
        return "Coyote";
    }

    /**
     * @brief Checks if the organism meets reproduction conditions.
     *
     * If the coyote has at least 900 points, a new coyote is created as an offspring.
     * The offspring's points are reset to 0 and the parent's points are reduced by 900.
     * If reproduction does not occur, the function returns nullptr.
     *
     * @return emp::Ptr<Organism> A smart pointer to the new offspring, or nullptr if reproduction did not occur.
     */
    emp::Ptr<Organism> CheckReproduction() {
        if (GetPoints() >= 900) {
            emp::Ptr<Coyote> offspring = new Coyote(*this);
            offspring->SetPoints(0);
            AddPoints(-900);
            return offspring;
        } else {
            return nullptr;
        }
    }

    /**
     * @brief Determines the outcome of an interaction with another organism.
     *
     * When interacting with another organism, if the other is a Cow, the coyote gains 200 points.
     * Regardless of the other organism's type, this coyote always takes precedence in the interaction.
     *
     * @param org_wp A smart pointer to the organism at the neighbor position.
     * @return emp::Ptr<Organism> A smart pointer to the winning organism (always this coyote).
     */
    emp::Ptr<Organism> Interact(emp::Ptr<Organism> org_wp) {
        if (org_wp->GetType() == "Cow") {
            AddPoints(200); // Gain points for eating a cow.
        }
        return this; // This coyote always takes precedence.
    }

};

#endif