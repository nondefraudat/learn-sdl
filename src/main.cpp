#include "app.hpp"

int main(const int argc, char* const argv[]) {
	return App::getInstance().exec();
}