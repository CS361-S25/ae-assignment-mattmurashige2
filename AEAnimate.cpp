#include "emp/math/Random.hpp"
#include "emp/web/Animate.hpp"
#include "emp/web/web.hpp"
#include "World.h"
#include "Org.h"
#include "Cow.h"
#include "Coyote.h"

emp::web::Document doc{"target"};

class AEAnimator : public emp::web::Animate {

    // arena width and height
    const int num_h_boxes = 30;
    const int num_w_boxes = 30;
    const double RECT_SIDE = 10;
    const double width{num_w_boxes * RECT_SIDE};
    const double height{num_h_boxes * RECT_SIDE};

    emp::web::Canvas canvas{width, height, "canvas"};

    private: emp::Random random{6};
    private: OrgWorld world{random};

    public:

    AEAnimator() {
        // shove canvas into the div
        // along with a control button
        doc << canvas;
        doc << GetToggleButton("Toggle");
        doc << GetStepButton("Step");
        doc << "This is an artificial ecology simulating the population fluctuations occurring in a predator-prey relationship. The grey squares represent coyotes, and the brown squares represent cows. The coyotes reproduce a lot slower than than the cows do, but coyotes can eat cows to gain points (i.e., energy), thus speeding up reproduction. This relationship can be seen in the oscillations of population density (i.e., more cows leads to more coyotes, fewer cows leads to fewer coyotes).";

        Organism* my_cow = new Cow(&random, 0);
        Organism* my_coyote = new Coyote(&random, 0);

        world.AddOrgAt(my_cow, 0);
        world.AddOrgAt(my_coyote, 1);
        world.Resize(10, 10);
        world.SetPopStruct_Grid(num_w_boxes, num_h_boxes);
    }

    /**
     * @brief Updates and draws the current state of the world on the canvas.
     *
     * Called on each animation frame, performing the following steps:
     * 1. Clears the canvas.
     * 2. Updates the world state by calling world.Update(), which processes organism actions.
     * 3. Iterates through each grid cell (based on num_w_boxes and num_h_boxes).
     * 4. For each grid position, checks if the world is occupied:
     *    - If occupied, retrieves the organism's color via getPop() and draws a rectangle in that color.
     *    - If not occupied, draws a green rectangle.
     *
     * This function provides the primary visualization loop for rendering the simulation.
     */
    void DoFrame() override {
        canvas.Clear();
        world.Update();
        int org_num = 0;
        for (int x = 0; x < num_w_boxes; x++){
            for (int y = 0; y < num_h_boxes; y++) {
                if (world.IsOccupied(org_num)) {
                    canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, 
                                world.getPop()[org_num]->getColor(), 
                                world.getPop()[org_num]->getColor());
                } else {
                    canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "green", "green");
                }
                org_num++;
            }
        }
    }
};

AEAnimator animator;

int main() {animator.Step();}