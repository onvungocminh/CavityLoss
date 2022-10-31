#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
#include "util.h"
#include "MBD_distance_2d.h"
#include <queue>
#include <stdio.h>
#include <stdlib.h> 
#include <math.h> 
#include <limits.h>
using namespace std;




void topology_error_3D(const int * img , const unsigned char * diff, int * saddle, int depth, 
                              int height, int width)
{
    int * mask = new int[depth * height * width];
    int * map = new int[depth * height * width];

    // Find Max Label
    int max_label = 0;
    for(int d = 0; d < depth; d++)
        for(int h = 0; h < height; h++)
            for (int w = 0; w < width; w++)
            {
                set_pixel<int>(saddle, depth, height, width, d, h, w, 0);
                set_pixel<int>(mask, depth, height, width, d, h, w, 0);  

                int lb = get_pixel<int>(img, depth, height, width, d, h, w);
                if (lb > max_label)
                    max_label = lb;
            } 



    //int dd[6] = { 1 , -1 , 0,  0, 0 ,  0};
    //int dh[6] = { 0 ,  0 , 1, -1, 0 ,  0};
    //int dw[6] = { 0 ,  0 , 0,  0, 1 , -1};

    // int dd[18] = { 1 , -1 , 0,  0, 0 ,  0, 1, -1,  1, -1, 1, -1,  1, -1, 0,  0,  0,  0 };
    // int dh[18] = { 0 ,  0 , 1, -1, 0 ,  0, 1, -1, -1,  1, 0,  0,  0,  0, 1, -1,  1, -1 };
    // int dw[18] = { 0 ,  0 , 0,  0, 1 , -1, 0,  0,  0,  0, 1, -1, -1,  1, 1, -1, -1,  1 };

    int dd[26] = { 1 , -1 , 0,  0, 0 ,  0, 1, -1,  1, -1, 1, -1,  1, -1, 0,  0,  0,  0, 1, -1, 1, -1, 1, -1, -1, 1   };
    int dh[26] = { 0 ,  0 , 1, -1, 0 ,  0, 1, -1, -1,  1, 0,  0,  0,  0, 1, -1,  1, -1, 1, -1, 1, -1,-1,  1,  1,-1   };
    int dw[26] = { 0 ,  0 , 0,  0, 1 , -1, 0,  0,  0,  0, 1, -1, -1,  1, 1, -1, -1,  1, 1, -1,-1,  1, 1, -1,  1,-1   };

    if (max_label > 0)
    {
        for(int d = 0; d < depth; d++)
            for(int h = 0; h < height; h++)
                for (int w = 0; w < width; w++)
                {

                    Point3D p;
                    p.d = d;
                    p.h = h;
                    p.w = w;
                    int img_type = get_pixel<int>(img, depth, height, width, p.d, p.h, p.w);

                    if (img_type > 0)
                    {
                        for (int n = 0 ; n < 26 ; n++)
                        {
                            int tmp_d  = p.d + dd[n]; 
                            int tmp_h  = p.h + dh[n];
                            int tmp_w  = p.w + dw[n];

                            if (tmp_d >= 0 and tmp_d < depth and tmp_h >= 0 and tmp_h < height and tmp_w >= 0 and tmp_w < width)
                            {
                                Point3D r;
                                r.d = tmp_d;
                                r.h = tmp_h;
                                r.w = tmp_w;
                                unsigned char diff_type = get_pixel<unsigned char>(diff, depth, height, width, r.d, r.h, r.w);

                                if (diff_type > 0)
                                {
                                    set_pixel<int>(mask, depth, height, width, p.d, p.h,p.w, img_type);

                                }
                            }
                        }
                    }
                }

        
        ///////////////////////////////   

        vector<queue<Point3D> > Q(1000);


        int init_dis = 0;
        for(int d = 0; d < depth; d++)
        {
            for(int h = 0; h < height; h++)
            {
                for (int w = 0; w < width; w++)
                {
                    Point3D p;
                    p.d = d;
                    p.h = h;
                    p.w = w;
                    int seed_type = get_pixel<int>(mask, depth, height, width, d, h, w);

                    if(seed_type > 0){
                        init_dis = 0;
                        Q[init_dis].push(p);
                        set_pixel<int>(map, depth, height, width, d, h, w, 0);                    
                    }
                    else{
                        init_dis = 1000;
                        set_pixel<int>(map, depth, height, width, d, h, w, 1000);                                        
                    }
                }
            }
        }


        // Proceed the propagation from the marker to all pixels in the image
        for (int lvl = 0; lvl < 1000; lvl++)
        {

            while (!Q[lvl].empty())
            {
                Point3D p = Q[lvl].front();
                Q[lvl].pop();

                int map_value_p = get_pixel<int>(map, depth, height, width, p.d, p.h, p.w);
                int mask_value_p = get_pixel<int>(mask, depth, height, width, p.d, p.h, p.w);


                for (int n1 = 0 ; n1 < 26 ; n1++)
                {
                    int tmp_d  = p.d + dd[n1];
                    int tmp_h  = p.h + dh[n1];
                    int tmp_w  = p.w + dw[n1];

                    if (tmp_d >= 0 and tmp_d < depth and tmp_h >= 0 and tmp_h < height and tmp_w >= 0 and tmp_w < width)
                    {
                        Point3D r;
                        r.d = tmp_d;
                        r.h = tmp_h;
                        r.w = tmp_w;

                        unsigned char diff_value_r = get_pixel<unsigned char>(diff, depth, height, width, r.d, r.h, r.w);
                        int mask_value_r = get_pixel<int>(mask, depth, height, width, r.d, r.h, r.w);
                        int map_value_r = get_pixel<int>(map, depth, height, width, r.d, r.h, r.w);


                        if (diff_value_r > 0)
                        {
                            if (mask_value_r != 0 and mask_value_r != mask_value_p)
                            { 
                                if (mask_value_r < mask_value_p)
                                    set_pixel<int>(saddle, depth, height, width, p.d, p.h, p.w, 1);
				else
                                    set_pixel<int>(saddle, depth, height, width, r.d, r.h, r.w, 1);
                            }

                            int tmp_dis = map_value_p + 1;

                            if (tmp_dis < map_value_r)
                            {
                                set_pixel<int>(map, depth, height, width, r.d, r.h, r.w, tmp_dis);
                                Q[tmp_dis].push(r);
                                set_pixel<int>(mask, depth, height, width, r.d, r.h, r.w, mask_value_p);

                            }
                        }
                    }
                }
            }
        }

    }

    delete mask;
    delete map;

}



