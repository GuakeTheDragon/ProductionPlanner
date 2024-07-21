#ifndef SATISRECIPE_H
#define SATISRECIPE_H

#include "satisitem.h"

class satisRecipe
{
public:
    int recipeID;
    satisRecipe* nextRecipe;
    satisItem* currentIngredient;
    satisItem* nextIngredient;
    satisRecipe():recipeID(0), nextRecipe(NULL), currentIngredient(NULL), nextIngredient(NULL) {};
    satisRecipe(int ID):recipeID(0), nextRecipe(NULL), currentIngredient(NULL), nextIngredient(NULL) {};
};

#endif // SATISRECIPE_H
