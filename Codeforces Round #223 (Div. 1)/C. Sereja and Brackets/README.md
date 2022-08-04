![image](https://user-images.githubusercontent.com/90430653/182776694-070ac53b-1218-4c1c-a4ef-249051cfd201.png)

![image](https://user-images.githubusercontent.com/90430653/182860353-1b53708f-8bba-465b-859d-5022a83a8b07.png)

拿5 11 舉例 

[5 12) -> [16 23)
### lT=0,lO=0,lC=0,rT=0,rO=0,rC=0
#### 最左邊 xx = 16 偶數 
#### 最右邊 yy = 23 奇數
```
yy--  yy = 22
int tmp = min (o[yy],rC); // tmp = 0
rT = rT + t[yy] + tmp;    // rT = 0 ()
rO = rO + o[yy] - tmp;    // rO = 0 (
rC = rC + c[yy] - tmp     // rC = 1 )
```
#### 最左邊 xx = 8 偶數 
#### 最右邊 yy = 11 奇數
```
yy--  yy = 10
int tmp = min (o[yy],rC); // tmp = 0
rT = rT + t[yy] + tmp;    // rT = 1 ()
rO = rO + o[yy] - tmp;    // rO = 0 (
rC = rC + c[yy] - tmp     // rC = 1 )
```
#### 最左邊 xx = 4 偶數 
#### 最右邊 yy = 5 奇數
```
yy--  yy = 4
int tmp = min (o[yy],rC); // tmp = 1 
rT = rT + t[yy] + tmp;    // rT = 3 ()
rO = rO + o[yy] - tmp;    // rO = 0 (
rC = rC + c[yy] - tmp     // rC = 1 )
```
#### 最左邊 xx = 2 偶數 
#### 最右邊 yy = 2 奇數
結束
#### lT = 0 ,lO = 0 ,lC = 0 ,rT = 3, rO = 0, rC = 1
```
return lT + rT + min(lO,rC); // lT = 0 , rT = 3, min(lO,rC) = 0
```
