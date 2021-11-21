
%{

#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.tab.h"
#include "sql/parser/lex.yy.h"
// #include "common/log/log.h" // 包含C++中的头文件

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct ParserContext {
  Query * ssql;
  size_t select_length;
  size_t condition_length;
  size_t from_length;
  size_t value_length;
  Value values[MAX_NUM];
  Condition conditions[MAX_NUM];
  Selects sub_selects[MAX_NUM];
  
  CompOp comp[MAX_NUM];
  char id[MAX_NUM];
  size_t data_num;
  size_t sub_select_num;
  RelAttr attr_list_stack[MAX_NUM][MAX_NUM];
  size_t attr_list_length_stack[MAX_NUM];
  size_t attr_list_stack_top;
	Value value_list_stack[MAX_NUM][MAX_NUM];
	size_t value_list_length_stack[MAX_NUM];
  size_t value_list_stack_top;
  Condition condition_list_stack[MAX_NUM][MAX_NUM];
  size_t condition_list_length_stack[MAX_NUM];
  size_t condition_list_stack_top;
 size_t comp_length;

//   Selects *cur_select;
} ParserContext;

//获取子串
char *substr(const char *s,int n1,int n2)/*从s中提取下标为n1~n2的字符组成一个新字符串，然后返回这个新串的首地址*/
{
  char *sp = malloc(sizeof(char) * (n2 - n1 + 2));
  int i, j = 0;
  for (i = n1; i <= n2; i++) {
    sp[j++] = s[i];
  }
  sp[j] = 0;
  return sp;
}

void yyerror(yyscan_t scanner, const char *str)
{
  ParserContext *context = (ParserContext *)(yyget_extra(scanner));
  query_reset(context->ssql);
  context->ssql->flag = SCF_ERROR;
  context->condition_length = 0;
  context->from_length = 0;
  context->select_length = 0;
  context->value_length = 0;
  context->ssql->sstr.insertion.value_num = 0;
  context->data_num = 0;
  context->sub_select_num = 0;
  context->attr_list_stack_top = 0;
  for (int i=0; i<MAX_NUM; i++) {
	  context->attr_list_length_stack[i] = 0;
  }
//   size_t value_list_length_stack[MAX_NUM];
  context->value_list_stack_top = 0;
	for (int i=0; i<MAX_NUM; i++) {
	  context->value_list_length_stack[i] = 0;
  }
//   size_t condition_list_length_stack[MAX_NUM];
  context->condition_list_stack_top = 0;
  for (int i=0; i<MAX_NUM; i++) {
	  context->condition_list_length_stack[i] = 0;
  }
 context->comp_length=0;
  printf("parse sql failed. error=%s", str);
}

ParserContext *get_context(yyscan_t scanner)
{
  return (ParserContext *)yyget_extra(scanner);
}

#define CONTEXT get_context(scanner)

%}

%define api.pure full
%lex-param { yyscan_t scanner }
%parse-param { void *scanner }

//标识tokens
%token  SEMICOLON
        CREATE
        DROP
        TABLE
        TABLES
        INDEX
        SELECT
		ASC
        DESC
        SHOW
        SYNC
        INSERT
        DELETE
        UPDATE
        LBRACE
        RBRACE
        COMMA
        TRX_BEGIN
        TRX_COMMIT
        TRX_ROLLBACK
        INT_T
        STRING_T
        FLOAT_T
		DATE_T
        HELP
        EXIT
        DOT //QUOTE
        INTO
        VALUES
        FROM
        WHERE
        AND
        SET
        ON
        LOAD
        DATA
        INFILE
        EQ
        LT
        GT
        LE
        GE
        NE
		INNER
		JOIN
		ORDER
		GROUP
		BY
		UNIQUE
		TEXT_T
		NOT
		NULL_T
		NULLABLE
		IS_T
		IN_T

%union {
  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
  char *string;
  int number;
  float floats;
	char *position;
}

%token <number> NUMBER
%token <floats> FLOAT 
%token <string> ID
%token <string> PATH
%token <string> SSS
%token <string> STAR
%token <string> STRING_V
%token <string> MAX
%token <string> MIN
%token <string> COUNT
%token <string> AVG

//非终结符

%type <number> type;
%type <condition1> condition;
%type <value1> value;
%type <number> number;

%%

commands:		//commands or sqls. parser starts here.
    /* empty */
    | commands command
    ;

command:
	  select  
	| insert
	| update
	| delete
	| create_table
	| drop_table
	| show_tables
	| desc_table
	| create_index	
	| drop_index
	| sync
	| begin
	| commit
	| rollback
	| load_data
	| help
	| exit
    ;

exit:			
    EXIT SEMICOLON {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    };

help:
    HELP SEMICOLON {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    };

sync:
    SYNC SEMICOLON {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
    ;

begin:
    TRX_BEGIN SEMICOLON {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
    ;

commit:
    TRX_COMMIT SEMICOLON {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
    ;

rollback:
    TRX_ROLLBACK SEMICOLON {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
    ;

drop_table:		/*drop table 语句的语法解析树*/
    DROP TABLE ID SEMICOLON {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, $3);
    };

show_tables:
    SHOW TABLES SEMICOLON {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
    ;

desc_table:
    DESC ID SEMICOLON {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, $2);
    }
    ;

create_index:		/*create index 语句的语法解析树*/
	CREATE INDEX ID ON ID LBRACE id_def id_def_list RBRACE SEMICOLON  
		{
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, $3, $5);
		}
	| CREATE UNIQUE INDEX ID ON ID LBRACE id_def id_def_list RBRACE SEMICOLON 
		{
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_unique_index_init(&CONTEXT->ssql->sstr.create_index, $4, $6);
		}
    ;
id_def_list:
	/* empty */
	| COMMA id_def id_def_list {    }
	;

id_def:
	ID
		{
			create_index_append_attribute(&CONTEXT->ssql->sstr.create_index,$1);
		}
	;

drop_index:			/*drop index 语句的语法解析树*/
    DROP INDEX ID  SEMICOLON 
		{
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, $3);
		}
    ;
create_table:		/*create table 语句的语法解析树*/
    CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON 
		{
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, $3);
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
    ;
attr_def_list:
    /* empty */
    | COMMA attr_def attr_def_list {    }
    ;
    
attr_def:
    ID_get type LBRACE number RBRACE 
		{
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, $2, $4);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
			if ($2 == INTS_NULLABLE || $2 == FLOATS_NULLABLE || $2 == CHARS_NULLABLE || $2 == DATES_NULLABLE) {
				attr_info_init(&attribute, "NULL", IF_NULL, 4);
				create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
				CONTEXT->value_length++;
			}
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
			
		}
    |ID_get type
		{
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, $2, 4);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
			CONTEXT->value_length++;
			if ($2 == INTS_NULLABLE || $2 == FLOATS_NULLABLE || $2 == CHARS_NULLABLE || $2 == DATES_NULLABLE) {
				attr_info_init(&attribute, "NULL", IF_NULL, 4);
				create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
				CONTEXT->value_length++;
			}
		}
	|ID_get TEXT_T
		{
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, CHARS, 4096);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
    ;
number:
		NUMBER {$$ = $1;}
		;
type:
	INT_T { $$=INTS; }
	| INT_T NOT NULL_T { $$=INTS; }
	| INT_T NULLABLE { $$=INTS_NULLABLE; }
    | STRING_T { $$=CHARS; }
	| STRING_T NOT NULL_T { $$=CHARS; }
	| STRING_T NULLABLE { $$=CHARS_NULLABLE; }
    | FLOAT_T { $$=FLOATS; }
	| FLOAT_T NOT NULL_T { $$=FLOATS; }
	| FLOAT_T NULLABLE { $$=FLOATS_NULLABLE; }
	| DATE_T { $$=DATES; }
	| DATE_T NOT NULL_T { $$=DATES; }
	| DATE_T NULLABLE { $$=DATES_NULLABLE; }
    ;
ID_get:
	ID 
	{
		char *temp=$1; 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
	;

	
insert:				/*insert   语句的语法解析树*/
    INSERT INTO ID VALUES muti_value muti_value_list SEMICOLON 
		{
			// CONTEXT->values[CONTEXT->value_length++] = *$6;

			CONTEXT->ssql->flag=SCF_INSERT;//"insert";
			// CONTEXT->ssql->sstr.insertion.relation_name = $3;
			// CONTEXT->ssql->sstr.insertion.value_num = CONTEXT->value_length;
			// for(i = 0; i < CONTEXT->value_length; i++){
			// 	CONTEXT->ssql->sstr.insertion.values[i] = CONTEXT->values[i];
      // }
			inserts_init(&CONTEXT->ssql->sstr.insertion, $3, CONTEXT->values, CONTEXT->value_length, CONTEXT->data_num);

      //临时变量清零
      CONTEXT->value_length=0;
	  CONTEXT->data_num=0;
    }

muti_value_list:
	/* empty */
    | COMMA muti_value muti_value_list  { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
    ;
muti_value:
	LBRACE value value_list RBRACE {
		CONTEXT->data_num++;
	}
	;

value_list:
    /* empty */
    | COMMA value value_list  { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
    ;
value:
    NUMBER{	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
    |FLOAT{
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
    |SSS {
			$1 = substr($1,1,strlen($1)-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
    |NULL_T {
		// $1 = substr($1,1,strlen($1)-2);
  		// value_init_string(&CONTEXT->values[CONTEXT->value_length++], "null");
		  value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
	};
    
delete:		/*  delete 语句的语法解析树*/
    DELETE FROM ID where SEMICOLON 
		{
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, $3);
			// deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
			// 		CONTEXT->conditions, CONTEXT->condition_length);
			int stack_top = CONTEXT->condition_list_stack_top;
			printf("delete:stack_top:%d\n", stack_top);
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, CONTEXT->condition_list_stack[stack_top], CONTEXT->condition_list_length_stack[stack_top]);
			// selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_list_stack_top--;
			CONTEXT->condition_length = 0;	
    }
    ;
update:			/*  update 语句的语法解析树*/
    UPDATE ID SET ID EQ value where SEMICOLON
		{
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			// updates_init(&CONTEXT->ssql->sstr.update, $2, $4, value, 
			// 		CONTEXT->conditions, CONTEXT->condition_length);
			int stack_top = CONTEXT->condition_list_stack_top;
			printf("update:stack_top:%d\n", stack_top);
			updates_init(&CONTEXT->ssql->sstr.update, $2, $4, value, 
					CONTEXT->condition_list_stack[stack_top], CONTEXT->condition_list_length_stack[stack_top]);
			// deletes_set_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->condition_list_stack[stack_top], CONTEXT->condition_list_length_stack[stack_top]);
			// selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_list_stack_top--;
			CONTEXT->condition_length = 0;
		}
    ;
select:				/*  select 语句的语法解析树*/
    SELECT select_attr FROM ID rel_list where order_by group_by SEMICOLON
		{
			printf("do select\n");
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
			// selects_append_attributes(&CONTEXT->ssql->sstr.selection, CONTEXT->attr_list, CONTEXT->attr_list_length);
			// CONTEXT->cur_select = &CONTEXT->ssql->sstr.selection;
			int stack_top = CONTEXT->attr_list_stack_top;
			printf("select: attr stack_top:%d\n", stack_top);
			printf("CONTEXT->attr_list_length_stack[stack_top]:%d\n", CONTEXT->attr_list_length_stack[stack_top]);
			selects_append_attributes(&CONTEXT->ssql->sstr.selection, CONTEXT->attr_list_stack[stack_top], CONTEXT->attr_list_length_stack[stack_top]);
			CONTEXT->attr_list_stack_top--;
			
			selects_append_relation(&CONTEXT->ssql->sstr.selection, $4);
			stack_top = CONTEXT->condition_list_stack_top;
			printf("select:stack_top:%d\n", stack_top);
			selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->condition_list_stack[stack_top], CONTEXT->condition_list_length_stack[stack_top]);
			// selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_list_stack_top--;
			CONTEXT->ssql->flag=SCF_SELECT;//"select";
			// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;

			//临时变量清零
			CONTEXT->condition_length=0;
			CONTEXT->from_length=0;
			CONTEXT->select_length=0;
			CONTEXT->value_length = 0;
			CONTEXT->sub_select_num = 0;
			CONTEXT->sub_select_num = 0;
  			CONTEXT->attr_list_stack_top = 0;
			for (int i=0; i<MAX_NUM; i++) {
				CONTEXT->attr_list_length_stack[i] = 0;
			}
			//   size_t value_list_length_stack[MAX_NUM];
			CONTEXT->value_list_stack_top = 0;
			for (int i=0; i<MAX_NUM; i++) {
				CONTEXT->value_list_length_stack[i] = 0;
			}
			//   size_t condition_list_length_stack[MAX_NUM];
			CONTEXT->condition_list_stack_top = 0;
			for (int i=0; i<MAX_NUM; i++) {
				CONTEXT->condition_list_length_stack[i] = 0;
			}
			CONTEXT->comp_length=0;
			printf("do select end\n");
	}
	| SELECT select_attr FROM ID join_list SEMICOLON
	{
		printf("do select end\n");
		int stack_top = CONTEXT->attr_list_stack_top;
			selects_append_attributes(&CONTEXT->ssql->sstr.selection, CONTEXT->attr_list_stack[stack_top], CONTEXT->attr_list_length_stack[stack_top]);
			CONTEXT->attr_list_stack_top--;
		// selects_append_attributes(&CONTEXT->ssql->sstr.selection, CONTEXT->attr_list, CONTEXT->attr_list_length);
		// CONTEXT->cur_select = &CONTEXT->ssql->sstr.selection;
		selects_append_relation(&CONTEXT->ssql->sstr.selection, $4);
		stack_top = CONTEXT->condition_list_stack_top;
		printf("select:stack_top:%d\n", stack_top);
		selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->condition_list_stack[stack_top], CONTEXT->condition_list_length_stack[stack_top]);
		CONTEXT->condition_list_stack_top--;
		// selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);
		CONTEXT->ssql->flag=SCF_SELECT;//"select";
		// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;

		//临时变量清零
		CONTEXT->condition_length=0;
		CONTEXT->from_length=0;
		CONTEXT->select_length=0;
		CONTEXT->value_length = 0;
		CONTEXT->sub_select_num = 0;
		CONTEXT->sub_select_num = 0;
  		CONTEXT->attr_list_stack_top = 0;
		  for (int i=0; i<MAX_NUM; i++) {
				CONTEXT->attr_list_length_stack[i] = 0;
			}
		CONTEXT->value_list_stack_top = 0;
			for (int i=0; i<MAX_NUM; i++) {
				CONTEXT->value_list_length_stack[i] = 0;
			}
			//   size_t condition_list_length_stack[MAX_NUM];
			CONTEXT->condition_list_stack_top = 0;
			for (int i=0; i<MAX_NUM; i++) {
				CONTEXT->condition_list_length_stack[i] = 0;
			}
			CONTEXT->comp_length=0;
	}
	;

join_list:
	INNER JOIN ID ON condition condition_list {
		selects_append_relation(&CONTEXT->ssql->sstr.selection, $3);
	}
	| INNER JOIN ID ON condition condition_list join_list {
		selects_append_relation(&CONTEXT->ssql->sstr.selection, $3);
	};

select_attr:
    STAR {  
		printf("select *\n");
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			printf("CONTEXT->attr_list_stack_top: %d\n", CONTEXT->attr_list_stack_top);
			printf("CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]: %d\n", CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]);
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
			
		// printf("select * end\n");
		}
    | ID attr_list{
			RelAttr attr;
			relation_attr_init(&attr, NULL, $1);
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
		}
  	| ID DOT ID attr_list {
			RelAttr attr;
			relation_attr_init(&attr, $1, $3);
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
		}
	| ID DOT STAR attr_list {
			RelAttr attr;
			relation_attr_init(&attr, $1, "*");
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
		}
	| MAX LBRACE ID RBRACE attr_list{
			RelAttr attr;
			char* s=malloc(sizeof(char)*(3+strlen($3)+3));
			strcpy(s, "MAX(");
			// strcat(s, "(");
			strcat(s, $3);
			strcat(s, ")");
			relation_attr_init(&attr, NULL, s);
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
	}
	| MAX LBRACE ID DOT ID RBRACE attr_list{
			RelAttr attr;
			char* s=malloc(sizeof(char)*(3+strlen($5)+3));
			strcpy(s, "MAX(");
			// strcat(s, "(");
			strcat(s, $5);
			strcat(s, ")");
			relation_attr_init(&attr, $3, s);
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
	}
	| MIN LBRACE ID RBRACE attr_list{
			RelAttr attr;
			char* s=malloc(sizeof(char)*(3+strlen($3)+3));
			strcpy(s, "MIN(");
			// strcat(s, "(");
			strcat(s, $3);
			strcat(s, ")");
			relation_attr_init(&attr, NULL, s);
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
	}
	| MIN LBRACE ID DOT ID RBRACE attr_list{
			RelAttr attr;
			char* s=malloc(sizeof(char)*(3+strlen($5)+3));
			strcpy(s, "MIN(");
			// strcat(s, "(");
			strcat(s, $5);
			strcat(s, ")");
			relation_attr_init(&attr, $3, s);
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
	}
	| COUNT LBRACE ID RBRACE attr_list{
			RelAttr attr;
			char* s=malloc(sizeof(char)*(5+strlen($3)+3));
			strcpy(s, "COUNT(");
			// strcat(s, "(");
			strcat(s, $3);
			strcat(s, ")");
			relation_attr_init(&attr, NULL, s);
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
	}
	| COUNT LBRACE ID DOT ID RBRACE attr_list{
			RelAttr attr;
			char* s=malloc(sizeof(char)*(5+strlen($5)+3));
			strcpy(s, "COUNT(");
			// strcat(s, "(");
			strcat(s, $5);
			strcat(s, ")");
			relation_attr_init(&attr, $3, s);
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
	}
	| COUNT LBRACE STAR RBRACE {
			RelAttr attr;
			// char* s=malloc(sizeof(char)*(strlen($1)+4));
			// strcpy(s, $1);
			// strcat(s, "(*)");
			// strcat(s, $3);
			relation_attr_init(&attr, NULL, "COUNT(*)");
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
	}
	| AVG LBRACE ID RBRACE attr_list{
			RelAttr attr;
			char* s=malloc(sizeof(char)*(3+strlen($3)+3));
			strcpy(s, "AVG(");
			strcat(s, $3);
			strcat(s, ")");
			relation_attr_init(&attr, NULL, s);
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
	}
	| AVG LBRACE ID DOT ID RBRACE attr_list{
			RelAttr attr;
			char* s=malloc(sizeof(char)*(3+strlen($5)+3));
			strcpy(s, "AVG(");
			strcat(s, $5);
			strcat(s, ")");
			relation_attr_init(&attr, $3, s);
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
	}
    ; 


attr_list:
    /* empty */ {
		CONTEXT->attr_list_stack_top++;
	}
    | COMMA ID attr_list {
			RelAttr attr;
			relation_attr_init(&attr, NULL, $2);
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
    | COMMA ID DOT ID attr_list {
			RelAttr attr;
			relation_attr_init(&attr, $2, $4);
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
	| COMMA ID DOT STAR attr_list {
			RelAttr attr;
			relation_attr_init(&attr, $2, "*");
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
	| COMMA MAX LBRACE ID RBRACE attr_list {
			RelAttr attr;
			char* s=malloc(sizeof(char)*(3+strlen($4)+3));
			strcpy(s, "MAX(");
			// strcat(s, "(");
			strcat(s, $4);
			strcat(s, ")");
			relation_attr_init(&attr, NULL, s);
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
	}
	| COMMA MAX LBRACE ID DOT ID RBRACE attr_list {
			RelAttr attr;
			char* s=malloc(sizeof(char)*(3+strlen($6)+3));
			strcpy(s, "MAX(");
			// strcat(s, "(");
			strcat(s, $6);
			strcat(s, ")");
			relation_attr_init(&attr, $4, s);
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
	}
	| COMMA MIN LBRACE ID RBRACE attr_list {
			RelAttr attr;
			char* s=malloc(sizeof(char)*(3+strlen($4)+3));
			strcpy(s, "MIN(");
			// strcat(s, "(");
			strcat(s, $4);
			strcat(s, ")");
			relation_attr_init(&attr, NULL, s);
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
	}
	| COMMA MIN LBRACE ID DOT ID RBRACE attr_list {
			RelAttr attr;
			char* s=malloc(sizeof(char)*(3+strlen($6)+3));
			strcpy(s, "MIN(");
			// strcat(s, "(");
			strcat(s, $6);
			strcat(s, ")");
			relation_attr_init(&attr, $4, s);
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
	}
	| COMMA COUNT LBRACE ID RBRACE attr_list {
			RelAttr attr;
			char* s=malloc(sizeof(char)*(5+strlen($4)+3));
			strcpy(s, "COUNT(");
			// strcat(s, "(");
			strcat(s, $4);
			strcat(s, ")");
			relation_attr_init(&attr, NULL, s);
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
	}
	| COMMA COUNT LBRACE STAR RBRACE attr_list {
			RelAttr attr;
			relation_attr_init(&attr, NULL, "COUNT(*)");
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
	}
	| COMMA AVG LBRACE ID RBRACE attr_list {
			RelAttr attr;
			char* s=malloc(sizeof(char)*(3+strlen($4)+3));
			strcpy(s, "AVG(");
			// strcat(s, "(");
			strcat(s, $4);
			strcat(s, ")");
			relation_attr_init(&attr, NULL, s);
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
	}
	| COMMA AVG LBRACE ID DOT ID RBRACE attr_list {
			RelAttr attr;
			char* s=malloc(sizeof(char)*(3+strlen($6)+3));
			strcpy(s, "AVG(");
			// strcat(s, "(");
			strcat(s, $6);
			strcat(s, ")");
			relation_attr_init(&attr, $4, s);
			// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			attr_list_append_attribute(CONTEXT->attr_list_stack[CONTEXT->attr_list_stack_top], 
									CONTEXT->attr_list_length_stack[CONTEXT->attr_list_stack_top]++,
									&attr);
	};

rel_list:
    /* empty */
    | COMMA ID rel_list {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, $2);
		  }
    ;
where:
    /* empty */ {
		CONTEXT->condition_list_stack_top++;
		printf("condition_list: condition_list_stack_top++: %d\n", CONTEXT->condition_list_stack_top);
	}
    | WHERE condition condition_list {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
    ;

order_by:
	/* empty */ 
    | ORDER BY ID order_by_list {	
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, $3);
			Condition condition;
			condition_init(&condition, ORDER_BY_ASC, 1, &left_attr, NULL, 1, &left_attr, NULL);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									// CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									// &condition);
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
	}
	| ORDER BY ID ASC order_by_list {	
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, $3);
			Condition condition;
			condition_init(&condition, ORDER_BY_ASC, 1, &left_attr, NULL, 1, &left_attr, NULL);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
	}
	| ORDER BY ID DESC order_by_list {	
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, $3);
			Condition condition;
			condition_init(&condition, ORDER_BY_DESC, 1, &left_attr, NULL, 1, &left_attr, NULL);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
	}
	| ORDER BY ID DOT ID order_by_list {	
			RelAttr left_attr;
			relation_attr_init(&left_attr, $3, $5);
			Condition condition;
			condition_init(&condition, ORDER_BY_ASC, 1, &left_attr, NULL, 1, &left_attr, NULL);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
			}
	| ORDER BY ID DOT ID ASC order_by_list {	
			RelAttr left_attr;
			relation_attr_init(&left_attr, $3, $5);
			Condition condition;
			condition_init(&condition, ORDER_BY_ASC, 1, &left_attr, NULL, 1, &left_attr, NULL);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
			}
	| ORDER BY ID DOT ID DESC order_by_list {	
			RelAttr left_attr;
			relation_attr_init(&left_attr, $3, $5);
			Condition condition;
			condition_init(&condition, ORDER_BY_DESC, 1, &left_attr, NULL, 1, &left_attr, NULL);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
			}
    ;

order_by_list:
	/* empty */ {
		// CONTEXT->condition_list_stack_top++;
		// printf("condition_list: condition_list_stack_top++: %d\n", CONTEXT->condition_list_stack_top);
	}
    |COMMA ID order_by_list{
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, $2);
			Condition condition;
			condition_init(&condition, ORDER_BY_ASC, 1, &left_attr, NULL, 1, &left_attr, NULL);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
	}
	|COMMA ID ASC order_by_list{
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, $2);
			Condition condition;
			condition_init(&condition, ORDER_BY_ASC, 1, &left_attr, NULL, 1, &left_attr, NULL);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
	}
	|COMMA ID DESC order_by_list{
		RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, $2);
			Condition condition;
			condition_init(&condition, ORDER_BY_DESC, 1, &left_attr, NULL, 1, &left_attr, NULL);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
	}
	|COMMA ID DOT ID order_by_list{
		RelAttr left_attr;
			relation_attr_init(&left_attr, $2, $4);
			Condition condition;
			condition_init(&condition, ORDER_BY_ASC, 1, &left_attr, NULL, 1, &left_attr, NULL);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
	}
	|COMMA ID DOT ID ASC order_by_list{
		RelAttr left_attr;
			relation_attr_init(&left_attr, $2, $4);
			Condition condition;
			condition_init(&condition, ORDER_BY_ASC, 1, &left_attr, NULL, 1, &left_attr, NULL);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
	}
	|COMMA ID DOT ID DESC order_by_list{
		RelAttr left_attr;
			relation_attr_init(&left_attr, $2, $4);
			Condition condition;
			condition_init(&condition, ORDER_BY_DESC, 1, &left_attr, NULL, 1, &left_attr, NULL);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
	}
	;

group_by:
	/* empty */ 
    | GROUP BY ID group_by_list {	
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, $3);
			Condition condition;
			condition_init(&condition, GROUP_BY, 1, &left_attr, NULL, 1, &left_attr, NULL);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
	}
	| GROUP BY ID DOT ID group_by_list {	
			RelAttr left_attr;
			relation_attr_init(&left_attr, $3, $5);
			Condition condition;
			condition_init(&condition, GROUP_BY, 1, &left_attr, NULL, 1, &left_attr, NULL);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
			}
    ;

group_by_list:
	/* empty */ {
		// CONTEXT->condition_list_stack_top++;
		// printf("condition_list: condition_list_stack_top++: %d\n", CONTEXT->condition_list_stack_top);
	}
    |COMMA ID group_by_list{
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, $2);
			Condition condition;
			condition_init(&condition, GROUP_BY, 1, &left_attr, NULL, 1, &left_attr, NULL);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
	}
	|COMMA ID DOT ID group_by_list{
		RelAttr left_attr;
			relation_attr_init(&left_attr, $2, $4);
			Condition condition;
			condition_init(&condition, GROUP_BY, 1, &left_attr, NULL, 1, &left_attr, NULL);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
	}
	;


condition_list:
    /* empty */ {
		// CONTEXT->condition_list_stack_top++;
		// printf("condition_list: condition_list_stack_top++: %d\n", CONTEXT->condition_list_stack_top);
	}
    | AND condition condition_list {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
    ;

condition:
    ID comOp value 
		{
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, $1);

			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp[CONTEXT->comp_length-1], 1, &left_attr, NULL, 0, NULL, right_value);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name = NULL;
			// $$->left_attr.attribute_name= $1;
			// $$->comp = CONTEXT->comp[CONTEXT->comp_length-1];
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
		|value comOp value 
		{
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp[(CONTEXT->comp_length--)-1], 0, NULL, left_value, 0, NULL, right_value);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp = CONTEXT->comp[CONTEXT->comp_length-1];
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
		|ID comOp ID 
		{
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, $1);
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, $3);

			Condition condition;
			condition_init(&condition, CONTEXT->comp[(CONTEXT->comp_length--)-1], 1, &left_attr, NULL, 1, &right_attr, NULL);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=$1;
			// $$->comp = CONTEXT->comp[(CONTEXT->comp_length--)-1];
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;

		}
    |value comOp ID
		{
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, $3);

			Condition condition;
			condition_init(&condition, CONTEXT->comp[(CONTEXT->comp_length--)-1], 0, NULL, left_value, 1, &right_attr, NULL);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp=CONTEXT->comp[(CONTEXT->comp_length--)-1];
			
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;
		
		}
    |ID DOT ID comOp value
		{
			RelAttr left_attr;
			relation_attr_init(&left_attr, $1, $3);
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp[(CONTEXT->comp_length--)-1], 1, &left_attr, NULL, 0, NULL, right_value);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp=CONTEXT->comp[(CONTEXT->comp_length--)-1];
			// $$->right_is_attr = 0;   //属性值
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=NULL;
			// $$->right_value =*$5;			
							
    }
    |value comOp ID DOT ID
		{
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			RelAttr right_attr;
			relation_attr_init(&right_attr, $3, $5);

			Condition condition;
			condition_init(&condition, CONTEXT->comp[(CONTEXT->comp_length--)-1], 0, NULL, left_value, 1, &right_attr, NULL);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;//属性值
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp =CONTEXT->comp[(CONTEXT->comp_length--)-1];
			// $$->right_is_attr = 1;//属性
			// $$->right_attr.relation_name = $3;
			// $$->right_attr.attribute_name = $5;
									
    }
    |ID DOT ID comOp ID DOT ID
		{
			RelAttr left_attr;
			relation_attr_init(&left_attr, $1, $3);
			RelAttr right_attr;
			relation_attr_init(&right_attr, $5, $7);

			Condition condition;
			condition_init(&condition, CONTEXT->comp[(CONTEXT->comp_length--)-1], 1, &left_attr, NULL, 1, &right_attr, NULL);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;		//属性
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp =CONTEXT->comp[(CONTEXT->comp_length--)-1];
			// $$->right_is_attr = 1;		//属性
			// $$->right_attr.relation_name=$5;
			// $$->right_attr.attribute_name=$7;
    }
    | ID IS_T NULL_T {
		RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, $1);
			value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
			Condition condition;
			condition_init(&condition, IS, 1, &left_attr, NULL, 0, NULL, right_value);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
	}
	| ID IS_T NOT NULL_T {
		RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, $1);
			value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
			Condition condition;
			condition_init(&condition, IS_NOT, 1, &left_attr, NULL, 0, NULL, right_value);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
	}
	| ID DOT ID IS_T NULL_T {
		RelAttr left_attr;
			relation_attr_init(&left_attr, $1, $3);
			value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
			Condition condition;
			condition_init(&condition, IS, 1, &left_attr, NULL, 0, NULL, right_value);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
	}
	| ID DOT ID IS_T NOT NULL_T{
		RelAttr left_attr;
			relation_attr_init(&left_attr, $1, $3);
			value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
			Condition condition;
			condition_init(&condition, IS_NOT, 1, &left_attr, NULL, 0, NULL, right_value);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
	}
	|value IS_T NULL_T
		{
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
			Condition condition;
			condition_init(&condition, IS, 0, NULL, left_value, 0, NULL, right_value);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
		
		}
	|value IS_T NOT NULL_T
		{
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
			Condition condition;
			condition_init(&condition, IS_NOT, 0, NULL, left_value, 0, NULL, right_value);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
		
		}
	| ID comOp subselect 
		{
			// printf("where sub\n");
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, $1);

			Selects *right_select = &CONTEXT->sub_selects[CONTEXT->sub_select_num - 1];

			Condition condition;
			select_condition_init(&condition, CONTEXT->comp[(CONTEXT->comp_length--)-1], 1, &left_attr, NULL, right_select);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
			// printf("where sub end\n");

		}
	| ID DOT ID comOp subselect 
		{
			// printf("where sub\n");
			RelAttr left_attr;
			relation_attr_init(&left_attr, $1, $3);

			Selects *right_select = &CONTEXT->sub_selects[CONTEXT->sub_select_num - 1];

			Condition condition;
			select_condition_init(&condition, CONTEXT->comp[(CONTEXT->comp_length--)-1], 1, &left_attr, NULL, right_select);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);

		}
	| subselect comOp ID
		{
			printf("where sub\n");
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, $3);

			Selects *right_select = &CONTEXT->sub_selects[CONTEXT->sub_select_num - 1];

			Condition condition;
			if (CONTEXT->comp[(CONTEXT->comp_length--)-1] == LESS_THAN) {
				CONTEXT->comp[CONTEXT->comp_length] = GREAT_THAN;
			} else if (CONTEXT->comp[(CONTEXT->comp_length--)-1] == GREAT_THAN) {
				CONTEXT->comp[CONTEXT->comp_length] = LESS_THAN;
			} else if (CONTEXT->comp[(CONTEXT->comp_length--)-1] == LESS_EQUAL) {
				CONTEXT->comp[CONTEXT->comp_length] = GREAT_EQUAL;
			} else if (CONTEXT->comp[(CONTEXT->comp_length--)-1] == GREAT_EQUAL) {
				CONTEXT->comp[CONTEXT->comp_length] = LESS_EQUAL;
			}
			select_condition_init(&condition, CONTEXT->comp[CONTEXT->comp_length], 1, &left_attr, NULL, right_select);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			printf("CONTEXT->condition_list_stack_top: %d\n", CONTEXT->condition_list_stack_top);
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);
			// printf("where sub end\n");

		}
	| subselect comOp ID DOT ID 
		{
			// printf("where sub\n");
			RelAttr left_attr;
			relation_attr_init(&left_attr, $3, $5);

			Selects *right_select = &CONTEXT->sub_selects[CONTEXT->sub_select_num - 1];

			Condition condition;
			if (CONTEXT->comp[(CONTEXT->comp_length--)-1] == LESS_THAN) {
				CONTEXT->comp[CONTEXT->comp_length] = GREAT_THAN;
			} else if (CONTEXT->comp[(CONTEXT->comp_length--)-1] == GREAT_THAN) {
				CONTEXT->comp[CONTEXT->comp_length] = LESS_THAN;
			} else if (CONTEXT->comp[(CONTEXT->comp_length--)-1] == LESS_EQUAL) {
				CONTEXT->comp[CONTEXT->comp_length] = GREAT_EQUAL;
			} else if (CONTEXT->comp[(CONTEXT->comp_length--)-1] == GREAT_EQUAL) {
				CONTEXT->comp[CONTEXT->comp_length] = LESS_EQUAL;
			}
			select_condition_init(&condition, CONTEXT->comp[CONTEXT->comp_length], 1, &left_attr, NULL, right_select);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);

		}
	| subselect comOp subselect 
		{
			// printf("where sub\n");
			// RelAttr left_attr;
			// relation_attr_init(&left_attr, $3, $5);
			Selects *left_select = &CONTEXT->sub_selects[CONTEXT->sub_select_num - 1];
			Selects *right_select = &CONTEXT->sub_selects[CONTEXT->sub_select_num - 2];

			Condition condition;
			// if (CONTEXT->comp[(CONTEXT->comp_length--)-1] == LESS_THAN) {
			// 	CONTEXT->comp[CONTEXT->comp_length] = GREAT_THAN;
			// } else if (CONTEXT->comp[(CONTEXT->comp_length--)-1] == GREAT_THAN) {
			// 	CONTEXT->comp[CONTEXT->comp_length] = LESS_THAN;
			// } else if (CONTEXT->comp[(CONTEXT->comp_length--)-1] == LESS_EQUAL) {
			// 	CONTEXT->comp[CONTEXT->comp_length] = GREAT_EQUAL;
			// } else if (CONTEXT->comp[(CONTEXT->comp_length--)-1] == GREAT_EQUAL) {
			// 	CONTEXT->comp[CONTEXT->comp_length] = LESS_EQUAL;
			// }
			select_condition_init_(&condition, CONTEXT->comp[(CONTEXT->comp_length--)-1], left_select, right_select);
			// CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			condition_list_append_condition(CONTEXT->condition_list_stack[CONTEXT->condition_list_stack_top], 
									CONTEXT->condition_list_length_stack[CONTEXT->condition_list_stack_top]++,
									&condition);

		}
	;

comOp:
  	  EQ { CONTEXT->comp[CONTEXT->comp_length++] = EQUAL_TO; }
    | LT { CONTEXT->comp[CONTEXT->comp_length++] = LESS_THAN; }
    | GT { CONTEXT->comp[CONTEXT->comp_length++] = GREAT_THAN; }
    | LE { CONTEXT->comp[CONTEXT->comp_length++] = LESS_EQUAL; }
    | GE { CONTEXT->comp[CONTEXT->comp_length++] = GREAT_EQUAL; }
    | NE { CONTEXT->comp[CONTEXT->comp_length++] = NOT_EQUAL; }
	| IN_T { CONTEXT->comp[CONTEXT->comp_length++] = IN; }
	| NOT IN_T { CONTEXT->comp[CONTEXT->comp_length++] = NOT_IN; }
    ;

subselect:
	LBRACE SELECT select_attr FROM ID rel_list where RBRACE {
		printf("sub select\n");
		// selects_init_(&(CONTEXT->sub_selects[CONTEXT->sub_select_num]));
		// selects_move__(&(CONTEXT->sub_selects[CONTEXT->sub_select_num]), &CONTEXT->ssql->sstr.selection);
		// CONTEXT->cur_select = &(CONTEXT->sub_selects[CONTEXT->sub_select_num]);
		int stack_top = CONTEXT->attr_list_stack_top;
		selects_append_attributes(&CONTEXT->sub_selects[CONTEXT->sub_select_num], CONTEXT->attr_list_stack[stack_top], CONTEXT->attr_list_length_stack[stack_top]);
		CONTEXT->attr_list_length_stack[stack_top] = 0;
		CONTEXT->attr_list_stack_top--;
		// CONTEXT->attr_list_length = 0;
		
		selects_append_relation(&CONTEXT->sub_selects[CONTEXT->sub_select_num], $5);
		stack_top = CONTEXT->condition_list_stack_top;
		printf("stack top %d  sub_select_num:%d CONTEXT->condition_list_length_stack[stack_top]:%d\n", stack_top, CONTEXT->sub_select_num, CONTEXT->condition_list_length_stack[stack_top]);
		selects_append_conditions(&CONTEXT->sub_selects[CONTEXT->sub_select_num], CONTEXT->condition_list_stack[stack_top], CONTEXT->condition_list_length_stack[stack_top]);
		CONTEXT->condition_list_stack_top--;
		CONTEXT->ssql->flag=SCF_SELECT;
		CONTEXT->sub_select_num++;
		// printf("subselect end\n");
	}
	;

load_data:
		LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON
		{
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, $7, $4);
		}
		;
%%
//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, Query *sqls){
	ParserContext context;
	memset(&context, 0, sizeof(context));

	yyscan_t scanner;
	yylex_init_extra(&context, &scanner);
	context.ssql = sqls;
	scan_string(s, scanner);
	int result = yyparse(scanner);
	yylex_destroy(scanner);
	return result;
}
