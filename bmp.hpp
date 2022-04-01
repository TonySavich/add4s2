#pragma once
#include <iostream>
#include <fstream>
#pragma pack(1) // Отключить выравнивание
struct BMPHEADER
{
    unsigned short    Type;
    unsigned int      Size;
    unsigned short    Reserved1;
    unsigned short    Reserved2;
    unsigned int      OffBits;
};
#pragma pack()

#pragma pack(1)
struct BMPINFO
{
    unsigned int    Size;
    int             Width;
    int             Height;
    unsigned short  Planes;
    unsigned short  BitCount;
    unsigned int    Compression;
    unsigned int    SizeImage;
    int             XPelsPerMeter;
    int             YPelsPerMeter;
    unsigned int    ClrUsed;
    unsigned int    ClrImportant;
};
#pragma pack()

#pragma pack(1)
struct Pixel
{
    unsigned char b;
    unsigned char g;
    unsigned char r;
};
#pragma pack()

class BMP {
public:
    BMP() {

    }

    void read() {
        std::ifstream in("in.bmp", std::ios::binary);
        in.read(reinterpret_cast<char*>(&m_head), sizeof(BMPHEADER));

        in.read(reinterpret_cast<char*>(&m_inf), sizeof(BMPINFO));

        m_p = new Pixel * [m_inf.Height];
        for (int i = 0; i < m_inf.Height; i++)
            m_p[i] = new Pixel[m_inf.Width];

        for (int i = 0; i < m_inf.Height; i++)
        {
            for (int j = 0; j < m_inf.Width; j++)
                in.read(reinterpret_cast<char*>(&m_p[i][j]), sizeof(Pixel));

            if ((3 * m_inf.Width) % 4 != 0)
                for (int j = 0; j < 4 - (3 * m_inf.Width) % 4; j++)
                {
                    char c;
                    in.read(&c, 1);
                }
        }


        m_p_new = new Pixel * [m_inf.Height];
        for (int i = 0; i < m_inf.Height; i++)
            m_p_new[i] = new Pixel[m_inf.Width];
        for (int i = 0; i < m_inf.Height; i++)
        {
            for (int j = 0; j < m_inf.Width; j++)
            {
                m_p_new[i][j] = m_p[i][j];
            }
        }
    }






    void create() {


        std::ofstream out("out.bmp", std::ios::binary);

        int width = m_inf.Width;
        int height = m_inf.Height;



        m_head_new.Type = 0x4D42;
        m_head_new.Size = 14 + 40 + (3 * width * height);
        if (width % 4 != 0)
            m_head_new.Size += (4 - (3 * width) % 4) * height;
        m_head_new.OffBits = 54;
        m_head_new.Reserved1 = 0;
        m_head_new.Reserved2 = 0;

        out.write(reinterpret_cast<char*>(&m_head_new), sizeof(BMPHEADER));

        m_inf_new.BitCount = 24;
        m_inf_new.ClrImportant = 0;
        m_inf_new.ClrUsed = 0;
        m_inf_new.Compression = 0;
        m_inf_new.Height = height;
        m_inf_new.Planes = 1;
        m_inf_new.Size = 40;
        m_inf_new.SizeImage = m_head_new.Size - 54;
        m_inf_new.Width = width;
        m_inf_new.XPelsPerMeter = 0;
        m_inf_new.YPelsPerMeter = 0;

        out.write(reinterpret_cast<char*>(&m_inf_new), sizeof(BMPINFO));


        for (int i = 0; i < m_inf_new.Height; i++)
        {
            for (int j = 0; j < m_inf_new.Width; j++)
                out.write(reinterpret_cast<char*>(&m_p_new[i][j]), sizeof(Pixel));

            if ((3 * m_inf_new.Width) % 4 != 0)
                for (int j = 0; j < 4 - (3 * m_inf_new.Width) % 4; j++)
                {
                    char c = 0;
                    out.write(&c, 1);
                }
        }

    }




    void shifr(char f[10], int r) {
        int i = 0;
        for (int qq = 0; qq < r; qq++) {
            if (f[qq] == 'q'){
                m_p_new[3][i + 2].b +=1;
                m_p_new[3][i + 3].b+=1;
                m_p_new[2][i + 1].b+=1;
                m_p_new[2][i + 3].b+=1;
                m_p_new[1][i + 2].b+=1;
                m_p_new[1][i + 3].b+=1;
                m_p_new[0][i + 3].b+=1;
               
            }

            if (f[qq] == 'w') {
                m_p_new[3][i].b += 1;
                m_p_new[3][i + 3].b += 1;
                m_p_new[2][i].b += 1;
                m_p_new[2][i + 3].b += 1;
                m_p_new[1][i].b += 1;
                m_p_new[1][i+1].b += 1;
                m_p_new[1][i+2].b += 1;
                m_p_new[1][i + 3].b += 1;
                m_p_new[0][i].b += 1;
                m_p_new[0][i+3].b += 1;
            }


            if (f[qq] == 'e') {
                m_p_new[3][i].b += 1;
                m_p_new[3][i + 1].b += 1;
                m_p_new[2][i].b += 1;
                m_p_new[2][i + 1].b += 1;
                m_p_new[2][i + 2].b += 1;
                m_p_new[1][i].b += 1;
                m_p_new[0][i].b += 1;
                m_p_new[0][i + 1].b += 1;
            }

            if (f[qq] == 'r') {
                m_p_new[3][i].b += 1;
                m_p_new[3][i + 1].b += 1;
                m_p_new[2][i].b += 1;
                m_p_new[2][i + 2].b += 1;
                m_p_new[1][i].b += 1;
                m_p_new[1][i+1].b += 1;
                m_p_new[0][i].b += 1;
                m_p_new[0][i + 2].b += 1;
            }
            if (f[qq] == 't') {
                m_p_new[3][i+1].b += 1;
                m_p_new[2][i].b += 1;
                m_p_new[2][i+1].b += 1;
                m_p_new[2][i + 2].b += 1;
                m_p_new[1][i+1].b += 1;
                m_p_new[1][i + 3].b += 1;
                m_p_new[0][i+1].b += 1;
                m_p_new[0][i + 2].b += 1;
            }

            if (f[qq] == 'y') {
                m_p_new[3][i + 1].b += 1;
                m_p_new[3][i+3].b += 1;
                m_p_new[2][i + 1].b += 1;
                m_p_new[2][i + 3].b += 1;
                m_p_new[1][i + 2].b += 1;
                m_p_new[0][i + 2].b += 1;
            }
            if (f[qq] == 'o') {
                m_p_new[3][i + 1].b += 1;
                m_p_new[3][i+2].b += 1;
                m_p_new[2][i].b += 1;
                m_p_new[2][i + 3].b += 1;
                m_p_new[1][i].b += 1;
                m_p_new[1][i + 3].b += 1;
                m_p_new[0][i + 1].b += 1;
                m_p_new[0][i + 2].b += 1;
            }
            if (f[qq] == 'p') {
                m_p_new[3][i ].b += 1;
                m_p_new[3][i+1].b += 1;
                m_p_new[3][i + 2].b += 1;
                m_p_new[2][i ].b += 1;
                m_p_new[2][i + 2].b += 1;
                m_p_new[1][i ].b += 1;
                m_p_new[1][i + 1].b += 1;
                m_p_new[0][i].b += 1;
            }
            if (f[qq] == 'i') {
                m_p_new[3][i + 2].b += 1;    
                m_p_new[1][i + 2].b += 1;
                m_p_new[0][i + 2].b += 1;
            }
            if (f[qq] == 'u') {
                m_p_new[2][i].b += 1;
                m_p_new[2][i + 3].b += 1;
                m_p_new[1][i].b += 1;
                m_p_new[1][i + 3].b += 1;
                m_p_new[0][i + 1].b += 1;
                m_p_new[0][i + 2].b += 1;
            }

            if (f[qq] == 'a') {
                m_p_new[3][i + 2].b += 1;
                m_p_new[2][i ].b += 1;
                m_p_new[2][i+1].b += 1;
                m_p_new[2][i + 2].b += 1;
                m_p_new[1][i].b += 1;
                m_p_new[1][i + 2].b += 1;
                m_p_new[0][i ].b += 1;
                m_p_new[0][i + 1].b += 1;
                m_p_new[0][i+2].b += 1;
                m_p_new[0][i + 3].b += 1;
            }
          
            i = i + 5;
      }
        
        

    }





    void antishifr() {

         for (int i = 0; i < m_inf.Height; i++)
           for (int j = 0; j < m_inf.Width; j++)
            {
               
                   m_p_new[i][j].b *=100;
              
         
       
            }
    }

    ~BMP() {
        for (int i = 0; i < m_inf.Height; i++)
            delete[] m_p[i];
        delete[] m_p;

        for (int i = 0; i < m_inf_new.Height; i++)
            delete[] m_p_new[i];
        delete[] m_p_new;
    }
private:
    BMPHEADER m_head;
    BMPINFO m_inf;
    Pixel** m_p;
    Pixel** m_p_new;
    BMPHEADER m_head_new;
    BMPINFO m_inf_new;
};