#Tinh do lech chuan
sd(c(0.1, 0.15, 0.09))
# Tinh so lan lap
library(daewr)
Fpower1(alpha=0.05, nlev=2, nreps=3:10, Delta=0.05, sigma=0.032)
plan <- expand.grid(d=c(0.5,1.0), t1=-275, tdoduoc = -275)
plan
library(mefa)
experiment <- rep(plan,8)
experiment
# Ngau nhien dieu kien
(experiment <- experiment[sample(1:nrow(experiment)),])
# xuat ra file .csv
write.csv(experiment, 'experiment.csv', row.names=FALSE)
# doc file .csv sau khi thu thap du lieu
kq <-read.csv('experiment.csv')
kq
Mo hinh tuyen tinh
model <- lm(data=kq, formula = t1 ~ d + t2)
summary(model)
