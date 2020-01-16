//
// Created by yakir on 1/16/20.
//

#ifndef EX4_CACHEMANAGER_H
#define EX4_CACHEMANAGER_H


using namespace std;

template <class P, class S>
class CacheManager {
   virtual bool isThereSolution(P problem) = 0;
   virtual S getSolution(P problem) = 0;
   virtual void saveSolution(S solution) = 0;
};


#endif //EX4_CACHEMANAGER_H
