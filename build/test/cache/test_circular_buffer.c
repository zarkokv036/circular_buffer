#include "build/temp/_test_circular_buffer.c"
#include "src/circular_buffer.h"
#include "C:/Ruby27-x64/lib/ruby/gems/2.7.0/gems/ceedling-0.30.0/vendor/unity/src/unity.h"
static CircularBuffer_t emptyCircularBuffer(void *buffer, size_t capacity, size_t objectSize)

{



    memset(buffer, 0, capacity * objectSize);



    CircularBuffer_t cbuff;

    CircularBuffer_init(&cbuff, buffer, capacity, objectSize);

    return cbuff;

}



void setUp(void)

{



}



void tearDown(void)

{

}

void test_initFunction(void)

{

    uint64_t buffer[10];

    CircularBuffer_t cBuff = emptyCircularBuffer((buffer), sizeof(buffer) / sizeof(*buffer), sizeof(*buffer));



    const size_t objectSize = sizeof(*buffer);

    const size_t capacity = sizeof(buffer) / objectSize;



    int status;



    status = CircularBuffer_init(&cBuff, buffer, capacity, objectSize);

    UnityAssertEqualNumber((UNITY_INT)((CB_OK)), (UNITY_INT)((status)), (

   ((void *)0)

   ), (UNITY_UINT)(71), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((buffer)), (UNITY_INT)((cBuff.dataBuffer)), (

   ((void *)0)

   ), (UNITY_UINT)(72), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((10)), (UNITY_INT)((cBuff.capacity)), (

   ((void *)0)

   ), (UNITY_UINT)(73), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((sizeof(uint64_t))), (UNITY_INT)((cBuff.objectSize)), (

   ((void *)0)

   ), (UNITY_UINT)(74), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((cBuff.writeIndex)), (

   ((void *)0)

   ), (UNITY_UINT)(75), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((cBuff.readIndex)), (

   ((void *)0)

   ), (UNITY_UINT)(76), UNITY_DISPLAY_STYLE_INT);





    status = CircularBuffer_init(&cBuff, buffer, 0, objectSize);

    UnityAssertEqualNumber((UNITY_INT)((CB_BAD_PARAM)), (UNITY_INT)((status)), (

   ((void *)0)

   ), (UNITY_UINT)(80), UNITY_DISPLAY_STYLE_INT);



    status = CircularBuffer_init(&cBuff, buffer, capacity, 0);

    UnityAssertEqualNumber((UNITY_INT)((CB_BAD_PARAM)), (UNITY_INT)((status)), (

   ((void *)0)

   ), (UNITY_UINT)(83), UNITY_DISPLAY_STYLE_INT);



    status = CircularBuffer_init(&cBuff, 

                                        ((void *)0)

                                            , capacity, objectSize);

    UnityAssertEqualNumber((UNITY_INT)((CB_BAD_PARAM)), (UNITY_INT)((status)), (

   ((void *)0)

   ), (UNITY_UINT)(86), UNITY_DISPLAY_STYLE_INT);



    status = CircularBuffer_init(

                                ((void *)0)

                                    , buffer, capacity, objectSize);

    UnityAssertEqualNumber((UNITY_INT)((CB_BAD_PARAM)), (UNITY_INT)((status)), (

   ((void *)0)

   ), (UNITY_UINT)(89), UNITY_DISPLAY_STYLE_INT);





}

void test_inputParametars_of_putFunction(void)

{

    uint64_t buffer[10];

    CircularBuffer_t cBuff = emptyCircularBuffer((buffer), sizeof(buffer) / sizeof(*buffer), sizeof(*buffer));

    uint64_t item = 1;



    int status = CircularBuffer_put(&cBuff, &item);

    UnityAssertEqualNumber((UNITY_INT)((CB_OK)), (UNITY_INT)((status)), (

   ((void *)0)

   ), (UNITY_UINT)(108), UNITY_DISPLAY_STYLE_INT);

    status = CircularBuffer_put(&cBuff, 

                                       ((void *)0)

                                           );

    UnityAssertEqualNumber((UNITY_INT)((CB_BAD_PARAM)), (UNITY_INT)((status)), (

   ((void *)0)

   ), (UNITY_UINT)(110), UNITY_DISPLAY_STYLE_INT);

    status = CircularBuffer_put(

                               ((void *)0)

                                   , &item);

    UnityAssertEqualNumber((UNITY_INT)((CB_BAD_PARAM)), (UNITY_INT)((status)), (

   ((void *)0)

   ), (UNITY_UINT)(112), UNITY_DISPLAY_STYLE_INT);

}

void test_of_putFunction(void)

{

    uint64_t buffer[10];

    CircularBuffer_t cBuff = emptyCircularBuffer((buffer), sizeof(buffer) / sizeof(*buffer), sizeof(*buffer));



    for(size_t i = 0; i < cBuff.capacity; i++)

    {

        uint64_t value = i + 1;

        int status1 = CircularBuffer_put(&cBuff, &value);

        UnityAssertEqualNumber((UNITY_INT)((CB_OK)), (UNITY_INT)((status1)), (

       ((void *)0)

       ), (UNITY_UINT)(131), UNITY_DISPLAY_STYLE_INT);

        UnityAssertEqualNumber((UNITY_INT)((value)), (UNITY_INT)((buffer[i])), (

       ((void *)0)

       ), (UNITY_UINT)(132), UNITY_DISPLAY_STYLE_INT);



        UnityAssertEqualNumber((UNITY_INT)((i+1)), (UNITY_INT)((cBuff.count)), (

       ((void *)0)

       ), (UNITY_UINT)(134), UNITY_DISPLAY_STYLE_INT);

    }



}

void test_ForgetsOldest_putFunction(void)

{

    uint64_t buffer[10];

    CircularBuffer_t cBuff = emptyCircularBuffer((buffer), sizeof(buffer) / sizeof(*buffer), sizeof(*buffer));

    uint64_t item = 0;

    double s=3.542;

    UnityFail( (UnityStrErrDouble), (UNITY_UINT)((UNITY_UINT)(153)));



    while(cBuff.count < cBuff.capacity)

    {

        CircularBuffer_put(&cBuff, &item);

        item++;

    }





    for (size_t i = 0; i< cBuff.capacity; i++)

    {

        size_t prevReadIndex = cBuff.readIndex;



        uint64_t item = 0;

        UnityAssertEqualNumber((UNITY_INT)((CB_OK)), (UNITY_INT)((CircularBuffer_put(&cBuff, &item))), (

       ((void *)0)

       ), (UNITY_UINT)(167), UNITY_DISPLAY_STYLE_INT);





        UnityAssertEqualNumber((UNITY_INT)(((prevReadIndex + 1) % cBuff.capacity)), (UNITY_INT)((cBuff.readIndex)), (

       ((void *)0)

       ), (UNITY_UINT)(170), UNITY_DISPLAY_STYLE_INT);

        UnityAssertEqualNumber((UNITY_INT)((cBuff.writeIndex)), (UNITY_INT)((cBuff.readIndex)), (

       ((void *)0)

       ), (UNITY_UINT)(171), UNITY_DISPLAY_STYLE_INT);





        do {if ((cBuff.readIndex < cBuff.capacity)) {} else {UnityFail( ((" Expression Evaluated To FALSE")), (UNITY_UINT)((UNITY_UINT)(174)));}} while(0);

    }





        const uint64_t expectedBuffer[10] = { 0 };

        UnityFail( (UnityStrErr64), (UNITY_UINT)((UNITY_UINT)(179)));

}

void test_isEmptyFunction_isFullFunction(void) {

    uint64_t buffer[10];

    size_t size = 0;

    CircularBuffer_t cBuff = emptyCircularBuffer((buffer), sizeof(buffer) / sizeof(*buffer), sizeof(*buffer));



    UnityAssertEqualNumber((UNITY_INT)((CB_EMPTY)), (UNITY_INT)((CircularBuffer_isEmpty(&cBuff))), (

   ((void *)0)

   ), (UNITY_UINT)(194), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((CB_NOT_FULL)), (UNITY_INT)((CircularBuffer_isFull(&cBuff))), (

   ((void *)0)

   ), (UNITY_UINT)(195), UNITY_DISPLAY_STYLE_INT);



    CircularBuffer_getSize(&cBuff, &size);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((size)), (

   ((void *)0)

   ), (UNITY_UINT)(198), UNITY_DISPLAY_STYLE_INT);



    uint64_t item = 0;



    while (cBuff.count < (cBuff.capacity - 1))

    {

        CircularBuffer_put(&cBuff, &item);

        UnityAssertEqualNumber((UNITY_INT)((CB_NOT_EMPTY)), (UNITY_INT)((CircularBuffer_isEmpty(&cBuff))), (

       ((void *)0)

       ), (UNITY_UINT)(205), UNITY_DISPLAY_STYLE_INT);

        UnityAssertEqualNumber((UNITY_INT)((CB_NOT_FULL)), (UNITY_INT)((CircularBuffer_isFull(&cBuff))), (

       ((void *)0)

       ), (UNITY_UINT)(206), UNITY_DISPLAY_STYLE_INT);



        CircularBuffer_getSize(&cBuff, &size);

        UnityAssertEqualNumber((UNITY_INT)((cBuff.count)), (UNITY_INT)((size)), (

       ((void *)0)

       ), (UNITY_UINT)(209), UNITY_DISPLAY_STYLE_INT);

    }



    CircularBuffer_put(&cBuff, &item);



    UnityAssertEqualNumber((UNITY_INT)((CB_NOT_EMPTY)), (UNITY_INT)((CircularBuffer_isEmpty(&cBuff))), (

   ((void *)0)

   ), (UNITY_UINT)(214), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((CB_FULL)), (UNITY_INT)((CircularBuffer_isFull(&cBuff))), (

   ((void *)0)

   ), (UNITY_UINT)(215), UNITY_DISPLAY_STYLE_INT);





    CircularBuffer_getSize(&cBuff, &size);

    UnityAssertEqualNumber((UNITY_INT)((cBuff.capacity)), (UNITY_INT)((size)), (

   ((void *)0)

   ), (UNITY_UINT)(219), UNITY_DISPLAY_STYLE_INT);



    while (cBuff.count > 1)

    {

        CircularBuffer_get(&cBuff, &item);

        UnityAssertEqualNumber((UNITY_INT)((CB_NOT_EMPTY)), (UNITY_INT)((CircularBuffer_isEmpty(&cBuff))), (

       ((void *)0)

       ), (UNITY_UINT)(224), UNITY_DISPLAY_STYLE_INT);

        UnityAssertEqualNumber((UNITY_INT)((CB_NOT_FULL)), (UNITY_INT)((CircularBuffer_isFull(&cBuff))), (

       ((void *)0)

       ), (UNITY_UINT)(225), UNITY_DISPLAY_STYLE_INT);



        CircularBuffer_getSize(&cBuff, &size);

        UnityAssertEqualNumber((UNITY_INT)((cBuff.count)), (UNITY_INT)((size)), (

       ((void *)0)

       ), (UNITY_UINT)(228), UNITY_DISPLAY_STYLE_INT);

    }



    CircularBuffer_get(&cBuff, &item);



    UnityAssertEqualNumber((UNITY_INT)((CB_EMPTY)), (UNITY_INT)((CircularBuffer_isEmpty(&cBuff))), (

   ((void *)0)

   ), (UNITY_UINT)(233), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((CB_NOT_FULL)), (UNITY_INT)((CircularBuffer_isFull(&cBuff))), (

   ((void *)0)

   ), (UNITY_UINT)(234), UNITY_DISPLAY_STYLE_INT);



    CircularBuffer_getSize(&cBuff, &size);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((size)), (

   ((void *)0)

   ), (UNITY_UINT)(237), UNITY_DISPLAY_STYLE_INT);

}

void test_inputParametars_getFunction(void)

{

    uint64_t buffer[10];

    CircularBuffer_t cBuff = emptyCircularBuffer((buffer), sizeof(buffer) / sizeof(*buffer), sizeof(*buffer));



    uint64_t item;



    int status = CircularBuffer_get(&cBuff, &item);

    UnityAssertEqualNumber((UNITY_INT)((CB_EMPTY)), (UNITY_INT)((status)), (

   ((void *)0)

   ), (UNITY_UINT)(255), UNITY_DISPLAY_STYLE_INT);



    status = CircularBuffer_get(&cBuff, 

                                       ((void *)0)

                                           );

    UnityAssertEqualNumber((UNITY_INT)((CB_BAD_PARAM)), (UNITY_INT)((status)), (

   ((void *)0)

   ), (UNITY_UINT)(258), UNITY_DISPLAY_STYLE_INT);

    status = CircularBuffer_get(

                               ((void *)0)

                                   , &item);

    UnityAssertEqualNumber((UNITY_INT)((CB_BAD_PARAM)), (UNITY_INT)((status)), (

   ((void *)0)

   ), (UNITY_UINT)(260), UNITY_DISPLAY_STYLE_INT);

}

void test_indexesWith_getAndPutFunction(void)

{

    uint64_t buffer[10];

    CircularBuffer_t cBuff = emptyCircularBuffer((buffer), sizeof(buffer) / sizeof(*buffer), sizeof(*buffer));

    int status;





    for(size_t i = 0; i < 2 * cBuff.capacity; i++)

    {

        uint64_t item = i;

        status = CircularBuffer_put(&cBuff, &item);



        uint64_t getItem;

        status = CircularBuffer_get(&cBuff, &getItem);

        UnityAssertEqualNumber((UNITY_INT)((item)), (UNITY_INT)((getItem)), (

       ((void *)0)

       ), (UNITY_UINT)(285), UNITY_DISPLAY_STYLE_INT);

    }





    status = CircularBuffer_isEmpty(&cBuff);

    UnityAssertEqualNumber((UNITY_INT)((CB_EMPTY)), (UNITY_INT)((status)), (

   ((void *)0)

   ), (UNITY_UINT)(290), UNITY_DISPLAY_STYLE_INT);







    for(size_t i = 0; i < 2 * cBuff.capacity; i++)

    {

        uint64_t item = i;

        status = CircularBuffer_put(&cBuff, &item);

        UnityAssertEqualNumber((UNITY_INT)((CB_OK)), (UNITY_INT)((status)), (

       ((void *)0)

       ), (UNITY_UINT)(298), UNITY_DISPLAY_STYLE_INT);

    }

    for(size_t i = 0; i < cBuff.capacity; i++)

    {

        uint64_t item;

        status = CircularBuffer_get(&cBuff, &item);





    }

    UnityAssertEqualNumber((UNITY_INT)((cBuff.writeIndex)), (UNITY_INT)((cBuff.readIndex)), (

   ((void *)0)

   ), (UNITY_UINT)(307), UNITY_DISPLAY_STYLE_INT);

}

void test_inputParametars_getSizeFunction(void) {



    uint64_t buffer[10];

    CircularBuffer_t cBuff = emptyCircularBuffer((buffer), sizeof(buffer) / sizeof(*buffer), sizeof(*buffer));

    int status;

    uint64_t item;





    status = CircularBuffer_getSize(&cBuff, 

                                           ((void *)0)

                                               );

    UnityAssertEqualNumber((UNITY_INT)((CB_BAD_PARAM)), (UNITY_INT)((status)), (

   ((void *)0)

   ), (UNITY_UINT)(327), UNITY_DISPLAY_STYLE_INT);



    status = CircularBuffer_getSize(

                                   ((void *)0)

                                       , &item);

    UnityAssertEqualNumber((UNITY_INT)((CB_BAD_PARAM)), (UNITY_INT)((status)), (

   ((void *)0)

   ), (UNITY_UINT)(330), UNITY_DISPLAY_STYLE_INT);



    status = CircularBuffer_getSize(&cBuff, &item);

    UnityAssertEqualNumber((UNITY_INT)((CB_OK)), (UNITY_INT)((status)), (

   ((void *)0)

   ), (UNITY_UINT)(333), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((item)), (

   ((void *)0)

   ), (UNITY_UINT)(334), UNITY_DISPLAY_STYLE_INT);



}















void test_getSizeFunction(void) {



    uint64_t buffer[10];

    CircularBuffer_t cBuff = emptyCircularBuffer((buffer), sizeof(buffer) / sizeof(*buffer), sizeof(*buffer));

    int status;

    size_t size = 0;





    for (size_t i = 0; i < cBuff.capacity; i++)

    {

        uint64_t item1 = 1;

        status = CircularBuffer_put(&cBuff, &item1);



        status = CircularBuffer_getSize(&cBuff, &size);

        UnityAssertEqualNumber((UNITY_INT)((CB_OK)), (UNITY_INT)((status)), (

       ((void *)0)

       ), (UNITY_UINT)(358), UNITY_DISPLAY_STYLE_INT);

        UnityAssertEqualNumber((UNITY_INT)((i + 1)), (UNITY_INT)((size)), (

       ((void *)0)

       ), (UNITY_UINT)(359), UNITY_DISPLAY_STYLE_INT);



    }





    uint64_t value = 99;

    status = CircularBuffer_put(&cBuff, &value);

    status = CircularBuffer_getSize(&cBuff, &size);

    UnityAssertEqualNumber((UNITY_INT)((cBuff.capacity)), (UNITY_INT)((size)), (

   ((void *)0)

   ), (UNITY_UINT)(367), UNITY_DISPLAY_STYLE_INT);



    uint64_t item;



    while (cBuff.count > 0)

    {

       CircularBuffer_get(&cBuff, &item);

       status = CircularBuffer_getSize(&cBuff, &size);

       do {if ((cBuff.count == size)) {} else {UnityFail( ((" Expression Evaluated To FALSE")), (UNITY_UINT)((UNITY_UINT)(375)));}} while(0);

    }



    status = CircularBuffer_getSize(&cBuff, &size);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((size)), (

   ((void *)0)

   ), (UNITY_UINT)(379), UNITY_DISPLAY_STYLE_INT);

    CircularBuffer_get(&cBuff, &item);



    status = CircularBuffer_getSize(&cBuff, &size);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((size)), (

   ((void *)0)

   ), (UNITY_UINT)(383), UNITY_DISPLAY_STYLE_INT);

}

void test_bufferWithOneElement(void)

{

    uint8_t bufferSmallest[1];

    CircularBuffer_t cBuff;

    const size_t objectSizeS = sizeof(*bufferSmallest);

    const size_t capacityS = sizeof(bufferSmallest) / objectSizeS;

    size_t size = 0;



    int status = CircularBuffer_init(&cBuff, bufferSmallest, capacityS, objectSizeS);

    UnityAssertEqualNumber((UNITY_INT)((CB_OK)), (UNITY_INT)((status)), (

   ((void *)0)

   ), (UNITY_UINT)(402), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((UNITY_INT)((CB_EMPTY)), (UNITY_INT)((CircularBuffer_isEmpty(&cBuff))), (

   ((void *)0)

   ), (UNITY_UINT)(404), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((CB_NOT_FULL)), (UNITY_INT)((CircularBuffer_isFull(&cBuff))), (

   ((void *)0)

   ), (UNITY_UINT)(405), UNITY_DISPLAY_STYLE_INT);

    CircularBuffer_getSize(&cBuff, &size);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((size)), (

   ((void *)0)

   ), (UNITY_UINT)(407), UNITY_DISPLAY_STYLE_INT);



    uint8_t value = 1;

    UnityAssertEqualNumber((UNITY_INT)((CB_OK)), (UNITY_INT)((CircularBuffer_put(&cBuff, &value))), (

   ((void *)0)

   ), (UNITY_UINT)(410), UNITY_DISPLAY_STYLE_INT);

    CircularBuffer_getSize(&cBuff, &size);

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((size)), (

   ((void *)0)

   ), (UNITY_UINT)(412), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((UNITY_INT)((cBuff.writeIndex)), (UNITY_INT)((cBuff.readIndex)), (

   ((void *)0)

   ), (UNITY_UINT)(414), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((UNITY_INT)((CB_NOT_EMPTY)), (UNITY_INT)((CircularBuffer_isEmpty(&cBuff))), (

   ((void *)0)

   ), (UNITY_UINT)(416), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((CB_FULL)), (UNITY_INT)((CircularBuffer_isFull(&cBuff))), (

   ((void *)0)

   ), (UNITY_UINT)(417), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((UNITY_INT)((CB_OK)), (UNITY_INT)((CircularBuffer_get(&cBuff, &value))), (

   ((void *)0)

   ), (UNITY_UINT)(419), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((value)), (

   ((void *)0)

   ), (UNITY_UINT)(420), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((UNITY_INT)((cBuff.writeIndex)), (UNITY_INT)((cBuff.readIndex)), (

   ((void *)0)

   ), (UNITY_UINT)(422), UNITY_DISPLAY_STYLE_INT);



    CircularBuffer_getSize(&cBuff, &size);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((size)), (

   ((void *)0)

   ), (UNITY_UINT)(425), UNITY_DISPLAY_STYLE_INT);

}
