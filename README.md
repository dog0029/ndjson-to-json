# ndjson-to-json

## Requirement
- OpenCV

</br>
</br>

## ndjson과 json의 차이

- json은 파일의 처음과 끝의 괄호가 [ ]이고, ndjson은 각 그림마다 { }로 되어있다.
- json은 각 그림마다 , 로 구분되어 있지만 ndjson은 enter로 분리한다.

</br>
</br>

## 구현

### [ndjson2json.cpp](https://github.com/dog0029/ndjson-to-json/blob/main/ndjson2json/ndjson2json.cpp)
- ndjson 파일을 하나씩 조회하여 시작과 끝에 [와 ]를 삽입하고 맨 마지막 줄을 제외한 모든 문장의 끝에 ,를 삽입한다.
- ndjson 파일 예
    ```json
    {"license":"mit","count":"1551711"}
    {"license":"apache-2.0","count":"455316"}
    {"license":"gpl-2.0","count":"376453"}
    {"license":"gpl-3.0","count":"284761"}
    ```
- json 파일 예
    ```json
    [
        {"license":"mit","count":"1551711"},
        {"license":"apache-2.0","count":"455316"},
        {"license":"gpl-2.0","count":"376453"},
        {"license":"gpl-3.0","count":"284761"}
    ]
    ```

</br>

### [ndjson2json_1.cpp](https://github.com/dog0029/ndjson-to-json/blob/main/ndjson2json/ndjson2json_1.cpp)
- 하나의 ndjson 파일을 여러개의 json 파일로 변환한다.
- ndjson 파일 예
    ```javascript
    {"license":"mit","count":"1551711"}
    {"license":"apache-2.0","count":"455316"}
    {"license":"gpl-2.0","count":"376453"}
    {"license":"gpl-3.0","count":"284761"}
    ```
- json 파일 예
    ```javascript
    [{"license":"mit","count":"1551711"}]       // json file1 
    [{"license":"apache-2.0","count":"455316"}] // json file2
    [{"license":"gpl-2.0","count":"376453"}]    // json file3
    [{"license":"gpl-3.0","count":"284761"}]    // json file4
    ```