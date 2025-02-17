# ToDo
- [ ] 能看到界面和美化，但是服务器无法接收到消息
    需要调试

# AI Agent
## Frontend
`index.html`



# Web-server
## quick start
```bash
mkdir build
cd build

cmake ..
make
```
Run project
```bash
./OwnServer
```

## Requirements
Ubuntu 22.04.3 LTS

cmake version 3.22.1

git version 2.34.1

g++ 11.4.0

boost
```bash
dpkg -l | grep boost
```
version: `1.74.0-14ubuntu3`

## Something learned
- 模板函数需要在头文件完成实现，编译器需要在使用模板的地方生成具体代码
- const成员函数不能返回非const的引用
