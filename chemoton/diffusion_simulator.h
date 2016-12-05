#ifndef DIFFUSION_SIMULATOR_H
#define DIFFUSION_SIMULATOR_H
#include <cmath>
#include <stdlib.h>
using namespace std;
namespace gt {
class rdmap {
private:
    int mapsize;
    float f, k;
    float ru;
    float **u, **u_next;
public:
    rdmap() {}
    rdmap(int _mapsize, double _init_conc) : mapsize(_mapsize), f(0.03f), k(0.056f), ru(0.09f){
        u = static_cast<float**>(malloc(sizeof(float*)*mapsize));
        u[0] = static_cast<float*>(malloc(sizeof(float)*mapsize*mapsize));
        u_next = static_cast<float**>(malloc(sizeof(float*)*mapsize));
        u_next[0] = static_cast<float*>(malloc(sizeof(float)*mapsize*mapsize));
        for(int i = 1; i < mapsize; i++){
            u[i] = u[i-1] + mapsize;
            u_next[i] = u_next[i-1] + mapsize;
        }
        map_reset(_init_conc);
    }
    ~rdmap(){
        delete u[0];
        delete u;

        delete u_next[0];
        delete u_next;
    }

    void map_reset(double _init_conc){
        for(int i = 0; i < mapsize; i++){
            for(int j = 0; j < mapsize; j++){
                u[i][j] = 0.0;
                u_next[i][j] = 0.0;
            }
        }

        for(int i = 1; i < mapsize-1; i++){
            for(int j = 1; j < mapsize-1; j++){
                u[i][j] = 0.0;
            }
        }
        //const float init_param = 0.3;
        for(int i = 100; i < 102; i++){
            for(int j = 100; j < 102; j++){
                u[i][j] = _init_conc;
            }
        }
    }

    void point_delete(int x, int y, int range){
        int x_min = std::max(x-range, 0);
        int x_max = std::min(x+range, mapsize);
        int y_min = std::max(y-range, 0);
        int y_max = std::min(y+range, mapsize);

        for(int i = x_min; i < x_max; i++){
            for(int j = y_min; j < y_max; j++){
                u[i][j] = 0.0;
            }
        }
    }

    void move(){
        for(int i = 1; i < mapsize-1; i++){
            for(int j = 1; j < mapsize-1; j++){
                u_next[i][j] = static_cast<float>(1.0 * (ru * ((u[i][j-1] - 2*u[i][j] + u[i][j+1]) + (u[i-1][j] - 2*u[i][j] + u[i+1][j]))));
            }
        }

        for(int i = 1; i < mapsize-1; i++){
                u_next[i][0] = 0;
                u_next[i][mapsize-1] = 0;
                u_next[0][i] = 0;
                u_next[mapsize-1][i] = 0;
        }

        float** tmp;
        tmp = u;
        u = u_next;
        u_next = tmp;
    }

    void set_f(float _f){f = _f;}
    void set_k(float _k){k = _k;}
    void set_ru(float _ru){ru = _ru;}
    float get_f(){return f;}
    float get_k(){return k;}
    float get_ru(){return ru;}
    float** get_u(){
        return u;
    }
};
}
#endif // DIFFUSION_SIMULATOR_H
