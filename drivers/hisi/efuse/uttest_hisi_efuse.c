



#define BITS_WIDTH_MASK(num)  ((1<<(num))-1)
#define GET_GROUP_NUM(width_bit)            (((width_bit) + 31)/32)

static int calculat_group_numbers(int start, int width)
{
    int num = 1;
    while( ((start%32) + width) > 32)
    {
        num++;
        width -= (32 - (start%32));
        start = 0;
    }
    return num;
}
static void memory_move_read(int start, int width, unsigned int * buf_src, int group_src, unsigned int* buf_dst, int group_dst)
{
    int i;
    int len_front, len_behind;
    if((start%32) == 0)
    {
        for(i = 0; i < group_src; i++)
        {
            buf_dst[i] = buf_src[i];
            if(width < 32)
            {
                buf_dst[i] &= BITS_WIDTH_MASK(width);
            }
            else
            {
                width -= 32;
            }
        }
    }
    else if(((start%32)+width) <= 32)
    {
        buf_dst[0] = (buf_src[0] >> (start%32)) & BITS_WIDTH_MASK(width);
    }
    else
    {
        for(i=0; i < group_dst; i++)
        {
            len_front = start%32;
            len_behind = 32 - (start%32);
            buf_dst[i] =  ((buf_src[i] >> len_front) & BITS_WIDTH_MASK(len_behind));
            width -= len_behind;
            if( (i+1) < group_src)
            {
                if(width < len_front)
                    len_front = width;
                buf_dst[i] |=  ((buf_src[i+1] & BITS_WIDTH_MASK(len_front)) << len_behind);
                width -= len_front;
            }
        }
    }
    return;
}

static void memory_move_write(int start, int width, unsigned int * buf_src, int group_src, unsigned int* buf_dst, int group_dst)
{
    int i;
    int len_front, len_behind;
    for(i = 0; i < group_dst; i++)
    {
        buf_dst[i] = 0;
    }
    if((start%32) == 0)
    {
        for(i=0; i<group_src; i++)
        {
            buf_dst[i] = buf_src[i];
            if(width < 32)
            {
                buf_dst[i] &= BITS_WIDTH_MASK(width);
            }
            else
            {
                width -= 32;
            }
        }
    }
    else if(((start%32)+width) <= 32)
    {
        buf_dst[0] = (buf_src[0] & BITS_WIDTH_MASK(width)) << (start%32);
    }
    else
    {
        for(i=0; i < group_src; i++)
        {
            len_front = start%32;
            len_behind = 32 - (start%32);
            buf_dst[i] |=  (buf_src[i] & BITS_WIDTH_MASK(len_behind)) << len_front;
            width -= len_behind;
            if( (i+1)< group_dst)
            {
                if(width < len_front)
                    len_front = width;
                buf_dst[i+1] = ((buf_src[i] >> len_behind) & BITS_WIDTH_MASK(len_front));
                width -= len_front;
            }
        }
    }
    return;
}



int test_calculat_group_numbers(int start, int width)
{
    return calculat_group_numbers(start, width);
}



int test_memory_move_read_1(void)
{
    int buf_test1[4];
    int buf_test2[4];
    int group_read_from;
    int group_read_to;
    int group_write_from;
    int group_write_to ;

    buf_test1[0]=0x32100000;
    buf_test1[1]=0xba987654;
    group_read_from = calculat_group_numbers(20, 3);
    group_read_to = GET_GROUP_NUM(3);
    memory_move_read(20, 3, buf_test1, group_read_from, buf_test2, group_read_to);
    if(buf_test2[0] == 1)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

int test_memory_move_read_2(void)
{
    int buf_test1[4];
    int buf_test2[4];
    int group_read_from;
    int group_read_to;
    int group_write_from;
    int group_write_to ;

    buf_test1[0]=0x32100000;
    buf_test1[1]=0xba987654;
    group_read_from = calculat_group_numbers(20, 12);
    group_read_to = GET_GROUP_NUM(12);
    memory_move_read(20, 12, buf_test1, group_read_from, buf_test2, group_read_to);
    if(buf_test2[0] == 0x321)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

int test_memory_move_read_3(void)
{
    int buf_test1[4];
    int buf_test2[4];
    int group_read_from;
    int group_read_to;
    int group_write_from;
    int group_write_to ;

    buf_test1[0]=0x32100000;
    buf_test1[1]=0xba987654;
    group_read_from = calculat_group_numbers(20, 20);
    group_read_to = GET_GROUP_NUM(20);
    memory_move_read(20, 20, buf_test1, group_read_from, buf_test2, group_read_to);
    if(buf_test2[0] == 0x54321)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

int test_memory_move_read_4(void)
{
    int buf_test1[4];
    int buf_test2[4];
    int group_read_from;
    int group_read_to;
    int group_write_from;
    int group_write_to ;

    buf_test1[0]=0x32100000;
    buf_test1[1]=0xba987654;
    group_read_from = calculat_group_numbers(20, 44);
    group_read_to = GET_GROUP_NUM(44);
    memory_move_read(20, 44, buf_test1, group_read_from, buf_test2, group_read_to);
    if((buf_test2[0] == 0x87654321) && (buf_test2[1] == 0xba9))
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

int test_memory_move_read_5(void)
{
    int buf_test1[4];
    int buf_test2[4];
    int group_read_from;
    int group_read_to;
    int group_write_from;
    int group_write_to ;

    buf_test1[0]=0x00004321;
    buf_test1[1]=0xba987654;
    group_read_from = calculat_group_numbers(0, 8);
    group_read_to = GET_GROUP_NUM(8);
    memory_move_read(0, 8, buf_test1, group_read_from, buf_test2, group_read_to);
    if(buf_test2[0] == 0x21)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

int test_memory_move_read_6(void)
{
    int buf_test1[4];
    int buf_test2[4];
    int group_read_from;
    int group_read_to;
    int group_write_from;
    int group_write_to ;

    buf_test1[0]=0x32100000;
    buf_test1[1]=0xba987654;
    buf_test1[2]=0x87654321;
    group_read_from = calculat_group_numbers(20, 60);
    group_read_to = GET_GROUP_NUM(60);
    memory_move_read(20, 60, buf_test1, group_read_from, buf_test2, group_read_to);
    if(buf_test2[0] == 0x87654321 && buf_test2[1] == 0x04321ba9)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

int test_memory_move_write_1(void)
{
    int buf_test1[4];
    int buf_test2[4];
    int group_read_from;
    int group_read_to;
    int group_write_from;
    int group_write_to ;

    buf_test1[0]=0x87654321;
    buf_test1[1]=0x00000ba9;
    group_write_from = GET_GROUP_NUM(3);
    group_write_to = calculat_group_numbers(20, 3);
    memory_move_write(20, 3, buf_test1, group_write_from, buf_test2, group_write_to);
    if(buf_test2[0] == 0x100000)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

int test_memory_move_write_2(void)
{
    int buf_test1[4];
    int buf_test2[4];
    int group_read_from;
    int group_read_to;
    int group_write_from;
    int group_write_to ;

    buf_test1[0]=0x87654321;
    buf_test1[1]=0x00000ba9;
    group_write_from = GET_GROUP_NUM(12);
    group_write_to = calculat_group_numbers(20, 12);
    memory_move_write(20, 12, buf_test1, group_write_from, buf_test2, group_write_to);
    if(buf_test2[0] == 0x32100000)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

int test_memory_move_write_3(void)
{
    int buf_test1[4];
    int buf_test2[4];
    int group_read_from;
    int group_read_to;
    int group_write_from;
    int group_write_to ;

    buf_test1[0]=0x87654321;
    buf_test1[1]=0x00000ba9;
    group_write_from = GET_GROUP_NUM(20);
    group_write_to = calculat_group_numbers(20, 20);
    memory_move_write(20, 20, buf_test1, group_write_from, buf_test2, group_write_to);
    if(buf_test2[0] == 0x32100000 && buf_test2[1] == 0x54)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

int test_memory_move_write_4(void)
{
    int buf_test1[4];
    int buf_test2[4];
    int group_read_from;
    int group_read_to;
    int group_write_from;
    int group_write_to ;

    buf_test1[0]=0x87654321;
    buf_test1[1]=0x0fedcba9;
    group_write_from = GET_GROUP_NUM(44);
    group_write_to = calculat_group_numbers(20, 44);
    memory_move_write(20, 44, buf_test1, group_write_from, buf_test2, group_write_to);
    if(buf_test2[0] == 0x32100000 && buf_test2[1] == 0xba987654)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}
int test_memory_move_write_5(void)
{
    int buf_test1[4];
    int buf_test2[4];
    int group_read_from;
    int group_read_to;
    int group_write_from;
    int group_write_to ;

    buf_test1[0]=0x87654321;
    buf_test1[1]=0x0fedcba9;
    group_write_from = GET_GROUP_NUM(8);
    group_write_to = calculat_group_numbers(0, 8);
    memory_move_write(0, 8, buf_test1, group_write_from, buf_test2, group_write_to);
    if(buf_test2[0] == 0x21)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

int test_memory_move_write_6(void)
{
    int buf_test1[4];
    int buf_test2[4];
    int group_read_from;
    int group_read_to;
    int group_write_from;
    int group_write_to ;

    buf_test1[0]=0x87654321;
    buf_test1[1]=0xba987654;
    group_write_from = GET_GROUP_NUM(60);
    group_write_to = calculat_group_numbers(20, 60);
    memory_move_write(20, 60, buf_test1, group_write_from, buf_test2, group_write_to);
    if(buf_test2[0] == 0x32100000 && buf_test2[1] == 0x65487654 && buf_test2[2] == 0xa987)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}
