/**
 * \file boardloader.c
 * \brief Funções para carregar as informações pertinentes a monstros, terrenos, objetos, fases a partir de seus arquivos de dados
 *
 * \author João da Silva, Marina Salles, Ricardo Macedo
 */

#include "player.h"


/**
 * Carrega as definições de objetos de um arquivo de dados
 * \param definitions Estrutura de dados que armazena as definições
 * \param filename Nome do arquivo de dados (default: object.dat)
 */
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
			loadObjectDefinition(&definitions[(int)c], DATFILE);
		}
	}
	definitions[i].id = '-';

	fclose(DATFILE);
}

/**
 * Carrega as informações dos elementos de terreno de um arquivo
 * \param file  O arquivo com as informações
 * \param terrenos O lugar para armazenar as informações
 */
void loadTerrainDefinitions(Terrain terrenos[],char *file)
{
	FILE* arq;
	char nome[255], codigo;
	int passavel, x, y;
	char fullname[MAXLEN] = DATADIR;

	strcat(fullname, file);
	arq = fopen(fullname, "r");

	while ((codigo = fgetc(arq)) != EOF)
	{
		if (codigo == '\n' || codigo == '\r') continue;
		if (codigo == '#' || codigo == ' ')
		{
			while (codigo != '\n')
			{
				fscanf(arq, "%c", &codigo);
			}
			continue;
		}

		fscanf(arq, " %s %d %d %d", nome, &passavel, &y, &x);

		terrenos[(int)codigo].passavel = passavel;
		terrenos[(int)codigo].retangulo.x = x * TILE_WIDTH;
		terrenos[(int)codigo].retangulo.y = y * TILE_HEIGHT;
		terrenos[(int)codigo].retangulo.w = TILE_WIDTH;
		terrenos[(int)codigo].retangulo.h = TILE_HEIGHT;
	}

	fclose(arq);
}

/**
 * Lê uma linha do arquivo de definições de objetos e carrega um objeto-definição para futura referência
 * \param def Object a ser carregado com a definição
 * \param F leitor do arquivo de objeto
 */
void loadObjectDefinition(Object *def, FILE *F){
	char lixo[1000];
	int num, i;

	/* formato do arquivo de objeto:

	   id name image_pos.y image_pos.x HP expire movement_pattern [parameters] attack_others? attack_num {attack_pattern damage [parameters=range,  firerate]} immunities_num [immunities]

	 */

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

	loadMovementInfo(&def->movement, F);

	fscanf(F, " %d", &def->attackOthers);

	fscanf(F, " %d", &def->numAttacks);
	for(i=0; i<def->numAttacks; i++){
		loadAttackInfo(&def->attacks[i], F);
	};

	fscanf(F, " %d", &def->numImmunities);
	for(i=0; i<def->numImmunities; i++){
		loadImmunitiesInfo(&def->immunities[i], F);
	};
	/* Se sobrar algo depois nesta linha,  eh lixo */
	fgets(lixo,  1000,  F);
}

/**
 * Carrega uma fase a partir de um arquivo de fase
 * \param board Estrutura de dados que guarda as informações do tabuleiro/mapa
 * \param definitions Estrutura de dados que guarda as definições de objetos
 * \param file Arquivo de fase
 */
SDL_Rect *loadBoard(GameBoard *board, Object definitions[], char *file){
	/* fases de BOARD_HEIGHTxBOARD_WIDTH tiles*/
	char fullname[MAXLEN] = DATADIR;
	FILE *F;
	int i, j;
	char tile;
	SDL_Rect *player = malloc(sizeof(SDL_Rect));

	strcat(fullname, file);

	F = fopen(fullname, "r");

	if(F==NULL){
		player->x = -1;
		return player;
	}

	for(i =0;i<BOARD_HEIGHT;i++){
		for(j=0;j<BOARD_WIDTH;j++){
			fscanf(F, " %c", &tile);
			board->scenario[i][j] = tile;
			fscanf(F, "%c", &tile);
			if(tile == '@'){
				player->y = i;
				player->x = j;
			}
			else
				board->objects[i][j] = newObject(tile, definitions);
		}
	}
	fclose(F);
	return player;
}

/**
 * Cria novo objeto, cópia de uma definição
 * \param id Identificador do tipo de objeto
 * \param defs Lista de definições
 */
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

/**
 * Devolve endereço de uma definição
 * \param id Identificador do tipo de objeto
 * \param defs Lista de definições
 */
Object *searchObjectDefinition(char id,  Object defs[]){
	return &defs[(int)id];
}

/**
 * Copia um Object (usado para criar um objeto a partir das definições)
 */
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

/**
 * Copia uma estrutura do tipo movimento (usado para copiar objeto)
 */
void copyMovement(Movement *new, Movement *ref){
	new->pattern = ref->pattern;
	new->speed = ref->speed;
	new->direction.x = ref->direction.x;
	new->direction.y = ref->direction.y;
	new->expire = ref->expire;
}

/**
 * Copia uma estrutura do tipo ataque (usado para copiar objeto)
 */
void copyAttack(Attack *new, Attack *ref){
	new->type = ref->type;
	new->range = ref->range;
	new->firerate = ref->firerate;
	new->damage = ref->damage;
}

/**
 * Copia um retângulo
 */
void copyObjectClip(SDL_Rect *new,  SDL_Rect *ref){
	new->x = ref->x;
	new->y = ref->y;
	new->w = ref->w;
	new->h = ref->h;
}

/**
  Carrega informação de movimento do arquito de dados de objeto
 */
void loadMovementInfo(Movement *mov, FILE *F){
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

/**
 * Carrega informação de ataque do arquivo de dados de objeto 
 */
void loadAttackInfo(Attack *att, FILE *F){
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

/**
 * Carrega informação de imunidade do arquivo de dados de objeto */
void loadImmunitiesInfo(attackType *type, FILE *F){
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
