#include "teste.h"
void test_domain() {
	Melodie m{ 1, "1", "1", 1 };
	assert(m.get_id() == 1);
	assert(m.get_titlu() == "1");
	assert(m.get_artist() == "1");
	assert(m.get_rank() == 1);
}

void test_repo() {
	Repo repo{ "test.txt" };
	assert(repo.get_all().size() == 3);
	Melodie m = repo.find(1);
	assert(m.get_rank() == 1);
	repo.update(Melodie{ 1, "2", "2", 1 });
	assert(repo.find(1).get_artist() == "2");
	repo.sterge(1);
	assert(repo.get_all().size() == 2);
}

void test_service() {
	Repo repo{ "test.txt" };
	Service srv{ repo };
	assert(srv.get_sortate().size() == 2);
	assert(srv.get_sortate()[0].get_rank() == 7);
	assert(srv.nr_rank(0) == 0);
	assert(srv.nr_rank(7) == 1);
	assert(srv.nr_artist("7") == 1);
	assert(srv.nr_artist("999") == 0);
	assert(srv.find_id(7).get_artist() == "7");
	srv.update(7, "7", 7);
	assert(srv.find_id(7).get_artist() == "7");
	srv.sterge_id(7);
	assert(srv.get_sortate().size() == 1);
}

void test_all() {
	test_domain();
	test_repo();
	test_service();
}
