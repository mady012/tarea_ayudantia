#include<stdio.h>
#include<libpq-fe.h>

int main()
{
  PGconn *conexion;
	PGresult *resultado;
	int tuplas,campos,i,j;
    const char *consulta="select c.curso_id,c.docente_id,a.nota from cursos as c join asignaturas_cursadas as a on (c.curso_id=a.curso_id and seccion=30411)";
	const char *pghost="190.100.156.5";
	const char *pgport="5432";
	const char *pgoptions=NULL;
	const char *pgtty=NULL;
	const char *dbname="iswdb";
	const char *login="isw";
	const char *pwd="isw";
	
	printf("Conectando a la base de datos...\n");
	conexion=PQsetdbLogin(pghost,pgport,pgoptions,pgtty,dbname,login,pwd);
	if(PQstatus(conexion)==CONNECTION_BAD)
	{
		printf("Error al conectar con la base de datos\n");
		fprintf(stderr,"%s",PQerrorMessage(conexion));		
	}
	else
	{
		printf("Conexion establecida\n");
	}
	resultado=PQexec(conexion,consulta);
	if(PQresultStatus(resultado)==PGRES_TUPLES_OK)
	{
		tuplas=PQntuples(resultado);
		campos=PQnfields(resultado);
		printf("Se extrajeron %d tuplas\n",tuplas);
		printf("n°|curso_id|docente_id|nota\n");
		for(i=0;i<tuplas;i++)
		{
			printf("%d ",i);
			for(j=0;j<campos;j++)
			{
				printf("     %s",PQgetvalue(resultado,i,j));
			}
			printf("\n");
		}
		
	}
	else
	{
		printf("Problemas en la consulta\n");
	}
	printf("Saliendo del programa\n");
	PQfinish(conexion);
    printf("Fin del programa\n");
    return 0;
}
