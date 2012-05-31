#include "game.h"

void loadObjectDefinitions(Object definitions[], char *filename){
	char datfile[MAXLEN] = DATADIR;
	FILE *DATFILE = NULL;
	int i;
	char c;
	char lixo[1000];

	strcat(datfile, filename);

	DATFILE = fopen(datfile,  "r");
	if(DATFILE == NULL) return;

	for(i = 0; !feof(DATFILE); ){
		c = getc(DATFILE);
		if(c == '\n' || c == '#'){
			fgets(lixo, 1000, DATFILE);
			continue;
		}
		else{
			ungetc(c, DATFILE);
			getObjectDefinition(&definitions[i++], DATFILE);
		}
	}
	definitions[i].id = '-';

	fclose(DATFILE);
}


void getObjectDefinition(Object *def, FILE *F){
	char lixo[1000];
	int num, i;

	/*id name image_pos.y image_pos.x HP expire movement_pattern [parameters] attack_others? attack_num {attack_pattern damage [parameters=range,  firerate]} immunities_num [immunities] */
	
	fscanf(F, " %c", &def->id);

	fscanf(F, " %s", def->name);

	fscanf(F, " %d", &num);
	def->clip.y = num*TILE_HEIGHT;
	def->clip.h = TILE_HEIGHT;

	fscanf(F, " %d", &num);
	def->clip.x = num*TILE_WIDTH;
	def->clip.w = TILE_WIDTH;

	fscanf(F, " %d", &def->HP);
	fscanf(F, " %d", &def->expire);

	getMovementInfo(&def->movement, F);

	fscanf(F, " %d", &def->attackOthers);

	fscanf(F, " %d", &def->numAttacks);
	for(i=0; i<def->numAttacks; i++){
		getAttackInfo(&def->attacks[i], F);
	};

	fscanf(F, " %d", &def->numImmunities);
	for(i=0; i<def->numImmunities; i++){
		getImmunitiesInfo(&def->immunities[i], F);
	};
	/* Se sobrar algo depois nesta linha,  eh lixo */
	fgets(lixo,  1000,  F);
}
	
void loadBoard(GameBoard *board, Object definitions[], char *file){
	/* fases de BOARDHEIGHTxBOARDWIDTH tiles*/
	char fullname[MAXLEN] = DATADIR;
	FILE *F;
	int i, j;
	char tile;

	strcat(fullname, file);

	F = fopen(fullname, "r");
	if(F==NULL)return;

	for(i =0;i<BOARD_HEIGHT;i++){
		for(j=0;j<BOARD_WIDTH;j++){
			fscanf(F, " %c", &tile);
			switch(tile){
				case 'l':
					board->scenario[i][j] = LAND;
					break;
				case 'w':
				default:
					board->scenario[i][j] = WATER;
					break;
			}
			fscanf(F, "%c", &tile);
			board->objects[i][j] = newObject(tile, definitions);
		}
	}
	fclose(F);
}

Object *newObject(char id, Object defs[]){
	Object *ref, *new = NULL;

	if(id == '-') return NULL;

	ref = searchObjectDefinition(id, defs);

	if(ref == NULL){
		printf("Could not find definition for object id %c\n", id);
		return NULL;
	}
	
	new = malloc(sizeof(Object));
	copyObject(new, ref);
	return new;
}

Object *searchObjectDefinition(char id,  Object defs[]){
	int i;

	for(i = 0; defs[i].id != '-'; i++){
		if(defs[i].id == id) return &defs[i];
	}
	return NULL;
}

void copyObject(Object *new, Object *ref){
	int i;

	new->id = ref->id;
	strcpy(new->name, ref->name);
	new->HP = ref->HP;
	new->expire = ref->expire;
	new->attackOthers = ref->attackOthers;
	
	copyMovement(&new->movement, &ref->movement);
	
	new->numAttacks = ref->numAttacks;
	for(i=0;i < new->numAttacks; i++){
		copyAttack(&new->attacks[i], &ref->attacks[i]);
	}
	
	new->numImmunities = ref->numImmunities;
	for(i=0;i < new->numImmunities; i++){
		new->immunities[i] = ref->immunities[i];
	}

	copyObjectClip(&new->clip, &ref->clip);
}

void copyMovement(Movement *new, Movement *ref){
	new->pattern = ref->pattern;
	new->speed = ref->speed;
	new->direction.x = ref->direction.x;
	new->direction.y = ref->direction.y;
	new->expire = ref->expire;
}

void copyAttack(Attack *new, Attack *ref){
	new->type = ref->type;
	new->range = ref->range;
	new->firerate = ref->firerate;
	new->damage = ref->damage;
}

void copyObjectClip(SDL_Rect *new,  SDL_Rect *ref){
	new->x = ref->x;
	new->y = ref->y;
	new->w = ref->w;
	new->h = ref->h;
}
	
void getMovementInfo(Movement *mov, FILE *F){
	char word[MAXLEN];

	fscanf(F, " %s", word);

	switch(word[0]){
		case 'l':/*line*/
			mov->pattern = MOV_LINE;
			fscanf(F, " %d", &mov->speed);
			mov->expire = -1;
			break;
		case 'r':
		switch(word[4]){
		case 'o':/*random*/
			mov->pattern = MOV_RANDOM;
			fscanf(F, " %d", &mov->speed);
			mov->expire = -1;
			break;
		case 'l':/*randline*/
			mov->pattern = MOV_RANDLINES;
			fscanf(F, " %d", &mov->speed);
			fscanf(F, " %d", &mov->expire);
			break;
		default:;
		}
		break;
		case 'N':
		default:/*NONE*/
			mov->pattern = MOV_NONE;
			mov->expire = -1;
			break;
	}
}

void getAttackInfo(Attack *att, FILE *F){
	char word[MAXLEN];

	fscanf(F, " %s", word);

	switch(word[0]){
		case 't':
		switch(word[1]){
		case 'o': /*touch */
			att->type = ATT_TOUCH;
			fscanf(F, " %d", &att->damage);
			break;
		case 'a':
		default:/*tackle*/
			att->type = ATT_TACKLE;
			fscanf(F, " %d", &att->damage);
			break;
		}
		break;
		case 'm':/*magic*/
			att->type = ATT_MAGIC;
			fscanf(F, " %d", &att->damage);
			fscanf(F, " %d", &att->range);
			fscanf(F, " %d", &att->firerate);
			break;
		case 'a':/*arrow*/
			att->type = ATT_ARROW;
			fscanf(F, " %d", &att->damage);
			fscanf(F, " %d", &att->range);
			fscanf(F, " %d", &att->firerate);
			break;
		case 'c':/*cannon*/
		default:
			att->type = ATT_CANNON;
			fscanf(F, " %d", &att->damage);
			fscanf(F, " %d", &att->range);
			fscanf(F, " %d", &att->firerate);
			break;
	}

}
	
void getImmunitiesInfo(attackType *type, FILE *F){
	char word[MAXLEN];

	fscanf(F, " %s", word);

	switch(word[0]){
		case 't':
		switch(word[1]){
		case 'o': /*touch */
			*type = ATT_TOUCH;
			break;
		case 'a':
		default:/*tackle*/
			*type = ATT_TACKLE;
			break;
		}
		case 'm':/*magic*/
			*type = ATT_MAGIC;
			break;
		case 'a':/*arrow*/
			*type = ATT_ARROW;
			break;
		case 'c':/*cannon*/
			*type = ATT_CANNON;
			break;
		case 's':/*ship*/
		default:
			*type = ATT_SHIP;
			break;
	}
}
