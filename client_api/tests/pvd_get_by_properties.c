//for testing with dbus-service.py or main.py from pvdman

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pvd_api.h>

/*
 * usage: sudo ./example properties
 * - propertis must be json string
 * - example: {"type":"general", "pricing":"free", "name":"default", "id"=...}
 */

int main ( int argc, char *argv[] )
{
	int i = 0;
	char *props;
	struct pvd **pvd;

	if ( argc < 2 ) {
		fprintf ( stderr, "Usage: %s <properties>\n", argv[0]);
		return -1;
	}

	props = argv[1];

	printf ( "Requesting by properties: %s:\n", props );
	pvd = pvd_get_by_properties ( props );
	for (i = 0; pvd[i] != NULL; i++ ) {
		if ( pvd[i]->id[0] == 0 ) {
			printf ("No such pvd!\n" );
		} else {
			printf ("id:%s ns:%s iface:%s\n", pvd[i]->id, pvd[i]->ns, pvd[i]->iface );
			printf ("properties: %s\n\n", pvd[i]->properties );
		}
		free(pvd[i]->id);
		free(pvd[i]->ns);
		free(pvd[i]->iface);
		free(pvd[i]);
	}
	free(pvd);

	return 0;
}