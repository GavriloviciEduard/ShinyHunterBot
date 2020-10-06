#include <QApplication>
#include "shinyhunterservice.h"


int main(int argc, char* argv[])
{
	QApplication application(argc, argv);
	shiny_hunter::ShinyHunterService shinyHunterService;
	shinyHunterService.createWindowContainer();
	return application.exec();
}
