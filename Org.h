#ifndef ORG_H
#define ORG_H

#include "emp/math/Random.hpp"
#include "emp/tools/string_utils.hpp"
#include <string>

class Organism {
    private:
        double points;
        emp::Ptr<emp::Random> random;
        std::string color;

    public:
    Organism(emp::Ptr<emp::Random> _random, double _points=0.0, std::string _color="black") :
        points(_points), random(_random), color(_color) {;}

    /**
     * @brief Retrieves the current points of the organism.
     * 
     * @return int The current points value.
     */
    int GetPoints() { return points; }

    /**
     * @brief Sets the organism's points to a new value.
     * 
     * @param _in The new points value.
     */
    void SetPoints(double _in) { points = _in; }

    /**
     * @brief Adds a specified amount of points to the organism.
     * 
     * @param _in The number of points to add.
     */
    void AddPoints(double _in) { points += _in; }

    /**
     * @brief Retrieves the organism's color.
     * 
     * @return std::string The color as a string.
     */
    std::string GetColor() { return color; }

    /**
     * @brief Processes the organism, modifying its points.
     * 
     * Adds the provided points to the organism's current points.
     * 
     * @param points The points to add during processing.
     */
    void Process(int points) {
        this->points += points;
    }

    /**
     * @brief Retrieves the organism's color.
     * 
     * This virtual function can be overridden by subclasses to return a dynamic color.
     * 
     * @return std::string The color of the organism.
     */
    virtual std::string getColor() { return color; }

    /**
     * @brief Checks whether the organism should reproduce.
     * 
     * This virtual function should be overridden by derived classes to implement reproduction logic.
     * 
     * @return emp::Ptr<Organism> A smart pointer to a new organism (if reproduction occurs), or nullptr otherwise.
     */
    virtual emp::Ptr<Organism> CheckReproduction() {
        return nullptr;
    }

    /**
     * @brief Retrieves the type of the organism.
     * 
     * Provides a string representation of the organism's type. Derived classes may override this to
     * provide their specific type names.
     * 
     * @return std::string The type description of the organism.
     */
    virtual std::string GetType() {
        return "Organism";
    }

    /**
     * @brief Determines an organism's interaction with an organism on a neighboring square to which
     * this organism is trying to move.
     */
    virtual emp::Ptr<Organism> Interact(emp::Ptr<Organism> org_wp) {
        return nullptr;
    }

};
#endif