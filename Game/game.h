#include "headers.h"

typedef struct vector {
	int x,y;
}Vector;

/* terrain */
#define terrain int
#define LAND 101
#define WATER 102

/* attacks */
#define MAXATTACKS 3
#define MAXIMMUNITIES 10

#define attackType int
#define ATT_ARROW 10
#define ATT_CANNON 11
#define ATT_TOUCH 12
#define ATT_TACKLE 13
#define ATT_MAGIC 14
#define ATT_SHIP 16
#define ATT_BOMB 15

typedef struct att{
	attackType type;
	int range;
	int firerate;
	int damage;
} Attack;

/* movements */
#define movementPattern int
#define MOV_LINE 20
#define MOV_RANDOM 21
#define MOV_RANDLINES 22
#define MOV_NONE -20

typedef struct mov{
	movementPattern pattern;
	int speed;
	Vector direction;
	int expire;
} Movement;

/* Objects */
typedef struct obj{
	char name[MAXLEN];

	char id;
	int HP;
	int expire;
	bool attackOthers;

	Movement movement;

	int numAttacks;
	Attack attacks[MAXATTACKS];

	int numImmunities;
	attackType immunities[MAXIMMUNITIES];

	SDL_Rect clip;
}Object;

/* the board controller */
typedef struct gmboard{
	terrain scenario[BOARD_HEIGHT][BOARD_WIDTH];
	Object *objects[BOARD_HEIGHT][BOARD_WIDTH];
} GameBoard;

/* loaders */
void loadObjectDefinitions(Object definitions[],char *filename);
void getObjectDefinition(Object *definition,FILE *F);
void loadBoard(GameBoard *board,Object definitions[],char *file);
Object *newObject(char id,Object defs[]);
Object *searchObjectDefinition(char id, Object defs[]);

void getMovementInfo(Movement *mov,FILE *F);
void getAttackInfo(Attack *att,FILE *F);
void getImmunitiesInfo(attackType *type,FILE *F);

void copyObject(Object *new,Object *ref);
void copyMovement(Movement *new,Movement *ref);
void copyAttack(Attack *new,Attack *ref);
void copyObjectClip(SDL_Rect *new, SDL_Rect *ref);


/* acters */
void fireAttack(GameBoard *gameboard, Object *attacker, Vector direction, attackType type);
void moveObject(GameBoard *gameboard, Object *mover);
void updateGameboard(GameBoard *gameboard);
