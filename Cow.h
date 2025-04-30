#include "Org.h"
#include "emp/math/Random.hpp"
#include "emp/tools/string_utils.hpp"
#include <string>
#include "World.h"

#ifndef COW_H
#define COW_H


class Cow : public Organism {

    public:
    Cow(emp::Ptr<emp::Random> _random, double _points=0.0, std::string _color="brown") :
        Organism(_random, _points, _color) {;}

    /**
     * @brief Gets the type identifier of the organism.
     * 
     * This function returns a string representation of the organism's type.
     * 
     * @return std::string "Cow"
     */
    std::string GetType() {
        return "Cow";
    }

    /**
     * @brief Checks if the organism meets reproduction conditions.
     * 
     * If the cow has at least 300 points, a new cow is created as an offspring.
     * The offspring's points are reset to 0 and the parent's points are reduced by 300.
     * If reproduction does not occur, the function returns nullptr.
     * 
     * @return emp::Ptr<Organism> A smart pointer to the new offspring or nullptr if reproduction did not occur.
     */
    emp::Ptr<Organism> CheckReproduction() {
        if (GetPoints() >= 300) {
            emp::Ptr<Cow> offspring = new Cow(*this);
            offspring->SetPoints(0);
            AddPoints(-300);
            return offspring;
        } else {
            return nullptr;
        }
    }

    /**
     * @brief Determines the outcome of an interaction with another organism.
     * 
     * When interacting with another organism at a specific world position, 
     * if the neighbor organism is a Coyote, the neighbor takes precedence.
     * Otherwise, this cow takes precedence.
     * 
     * @param org_wp A smart pointer to the organism at the neighbor position.
     * @return emp::Ptr<Organism> The organism that wins the interaction.
     */
    emp::Ptr<Organism> Interact(emp::Ptr<Organism> org_wp) {
        if (org_wp->GetType() == "Coyote") {
            return org_wp;
        } else {
            return this;
        }
    }

};

#endif