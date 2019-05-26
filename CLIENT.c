#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <string.h>
#include <gtk/gtk.h>

struct gVars{
	int serverSock;
	char msg[100];
	char dest[100];
	char str[100];
	char username[10];
	char welcomeStorage[20];
	char welcomeUsername[10];
}vars;

void print(GtkEntry *entry, void *optional_data){
	strcpy (vars.msg, gtk_entry_get_text(GTK_ENTRY(entry)));
	strcpy(vars.dest, vars.username);
	strcat(vars.dest, vars.msg);
	if(strlen(vars.dest) <= strlen(vars.username)){
			printf("YOU CAN NOT SEND AN EMPTY MESSAGE SIR!\n");
	}
	else{
			send(vars.serverSock, vars.dest, strlen(vars.dest), 0);
			gtk_entry_set_text (entry, "");
	}
}


int main(int argc, char *argv[]) {

	printf("Enter a username, sir: ");
	scanf("%s", vars.username);
	strcpy(vars.welcomeUsername, vars.username);
	strcat(vars.username, ": ");
	struct sockaddr_in server;

	vars.serverSock = socket(AF_INET, SOCK_STREAM, 0);
	server.sin_family = AF_INET;
	server.sin_port = htons(3002);
	inet_pton(AF_INET, "xxx.xxx.xx.xxx", &server.sin_addr); //xxx.xxx.xx.xxx = YOUR COMPUTER IP
	connect(vars.serverSock, (struct sockaddr *)&server, sizeof(server));

	gtk_init(&argc, &argv);
	GtkWidget *window, *entry, *grid, *instrLabel, *welcomeLabel;

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	gtk_window_set_title (GTK_WINDOW (window), vars.welcomeUsername);
	grid = gtk_grid_new();
  	gtk_container_add(GTK_CONTAINER(window), grid);

	entry = gtk_entry_new();
	g_signal_connect(entry, "activate", G_CALLBACK(print), NULL);
	gtk_grid_attach(GTK_GRID(grid), entry, 1, 1, 4, 1);

	instrLabel = gtk_label_new("Enter a msg: ");
	gtk_grid_attach(GTK_GRID(grid), instrLabel, 0, 1, 1, 1);

	strcpy(vars.welcomeStorage, "Welcome Mr ");
	strcat(vars.welcomeStorage, vars.welcomeUsername);

	welcomeLabel = gtk_label_new(vars.welcomeStorage);
	gtk_grid_attach(GTK_GRID(grid), welcomeLabel, 0, 0, 1, 1);

	gtk_widget_show_all(window);
	gtk_window_set_default_size(GTK_WINDOW(window), 500, 150);
	gtk_window_set_resizable (GTK_WINDOW(window), FALSE);

	gtk_main();
}
