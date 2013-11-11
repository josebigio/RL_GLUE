program main

double precision x(10)
double precision f(1)

iunit=10
open(unit=iunit,file="main.out",status="unknown")

do i=1,6
  x(i)=rand(0)
enddo

imorph=1
call warp_interface(x,5,f,1,imorph)
write(iunit,*) "morphing technique", imorph
do i=1,5
  write(iunit,*) "x(",i,") =", x(i)
enddo
write(iunit,*) "f =",f

imorph=2
call warp_interface(x,5,f,1,imorph)
write(iunit,*) "morphing technique", imorph
do i=1,5
  write(iunit,*) "x(",i,") =", x(i)
enddo
write(iunit,*) "f =",f

imorph=3
call warp_interface(x,6,f,1,imorph)
write(iunit,*) "morphing technique", imorph
do i=1,5
  write(iunit,*) "x(",i,") =", x(i)
enddo
write(iunit,*) "f =",f

close(iunit)

end !program



subroutine warp_interface(x,nx,f,nf,imorph)
! x  design variables vector
! nx design variables vector dimension
!
! f  objective functions vector
! nf objective function dimension
!
! imorph morphing technique flag:
!    1: technique 1A
!    2: technique 1B
!    3: technique 2
! see Diez M, Peri D, Stern F, Campana EF, "An Uncertainty Quantification Approach to Assess Geometry-Optimization Research Spaces through Karhunen-Loeeve Expansion", SIAM UQ12 Conference, 2012.

double precision x(nx), f(nf)
double precision raux1(5), raux2(5)
double precision geomi(2625*5,6)
double precision geomo(2625*5,6)
double precision gmorphi(2625*5)
double precision gmorpho(2625*5)
double precision w(6),pr
integer imorph

iunit1i=11
iunit1o=12
iunit2i=21
iunit2o=22
iunit3i=31
iunit3o=32
iunit4i=41
iunit4o=42
iunit5i=51
iunit5o=52
iunit6i=61
iunit6o=62

print *, "morphing technique ", imorph
if ((imorph==1).or.(imorph==3)) then
  open(unit=iunit1i,file='./geoms/surf0i.grd',status="old")
  open(unit=iunit1o,file='./geoms/surf0o.grd',status="old")
  open(unit=iunit2i,file='./geoms/surf1i.grd',status="old")
  open(unit=iunit2o,file='./geoms/surf1o.grd',status="old")
  open(unit=iunit3i,file='./geoms/surf2i.grd',status="old")
  open(unit=iunit3o,file='./geoms/surf2o.grd',status="old")
  open(unit=iunit4i,file='./geoms/surf3i.grd',status="old")
  open(unit=iunit4o,file='./geoms/surf3o.grd',status="old")
  open(unit=iunit5i,file='./geoms/surf4i.grd',status="old")
  open(unit=iunit5o,file='./geoms/surf4o.grd',status="old")
  open(unit=iunit6i,file='./geoms/surf5i.grd',status="old")
  open(unit=iunit6o,file='./geoms/surf5o.grd',status="old")
endif
if (imorph==2) then
  open(unit=iunit1i,file='./geoms/surf2i.grd',status="old")
  open(unit=iunit1o,file='./geoms/surf2o.grd',status="old")
  open(unit=iunit2i,file='./geoms/surf5i.grd',status="old")
  open(unit=iunit2o,file='./geoms/surf5o.grd',status="old")
  open(unit=iunit3i,file='./geoms/surf0i.grd',status="old")
  open(unit=iunit3o,file='./geoms/surf0o.grd',status="old")
  open(unit=iunit4i,file='./geoms/surf1i.grd',status="old")
  open(unit=iunit4o,file='./geoms/surf1o.grd',status="old")
  open(unit=iunit5i,file='./geoms/surf4i.grd',status="old")
  open(unit=iunit5o,file='./geoms/surf4o.grd',status="old")
  open(unit=iunit6i,file='./geoms/surf3i.grd',status="old")
  open(unit=iunit6o,file='./geoms/surf3o.grd',status="old")
endif

do igeom=1,6
  if (igeom==1) then
    iunitaux1=iunit1i
    iunitaux2=iunit1o
  endif
  if (igeom==2) then
    iunitaux1=iunit2i
    iunitaux2=iunit2o
  endif
  if (igeom==3) then
    iunitaux1=iunit3i
    iunitaux2=iunit3o
  endif
  if (igeom==4) then
    iunitaux1=iunit4i
    iunitaux2=iunit4o
  endif
  if (igeom==5) then
    iunitaux1=iunit5i
    iunitaux2=iunit5o
  endif
  if (igeom==6) then
    iunitaux1=iunit6i
    iunitaux2=iunit6o
  endif

  read(iunitaux1,*)
  read(iunitaux1,*)
  read(iunitaux2,*)
  read(iunitaux2,*)
  
  iaux=1
  do i=1,2625
    read(iunitaux1,*) (raux1(j),j=1,5)
    read(iunitaux2,*) (raux2(j),j=1,5)
    do j=1,5
      geomi(iaux,igeom)=raux1(j)
      geomo(iaux,igeom)=raux2(j)
      iaux=iaux+1
    enddo
  enddo
enddo

close(iunit1i)
close(iunit1o)
close(iunit2i)
close(iunit2o)
close(iunit3i)
close(iunit3o)
close(iunit4i)
close(iunit4o)
close(iunit5i)
close(iunit5o)
close(iunit6i)
close(iunit6o)

! morphing 1,2
if ((imorph==1).or.(imorph==2)) then
  do i=1,6
    pr=1.d0
    if (i==1) then
      w(i)=x(i)
    else
      do j=1,(i-1)
        pr=pr*(1.d0-x(j));
      enddo
      if (i.lt.6) w(i)=pr*x(i)
      if (i==6)   w(i)=pr
    endif
  enddo
endif

! morphing 3
if (imorph==3) then
  do i=1,6
    w(i)=x(i)
  enddo
  wsum=sum(w(1:6))
  w(1:6)=w(1:6)/wsum
endif

gmorphi=matmul(geomi,w)
gmorpho=matmul(geomo,w)

open(unit=101,file="gmorphi.grd",status="unknown")
open(unit=102,file="gmorpho.grd",status="unknown")

write(101,*) 1
write(101,*) 125, 35, 1

write(102,*) 1
write(102,*) 125, 35, 1

do i=1,2625*5
  write(101,*) gmorphi(i)
  write(102,*) gmorpho(i)
enddo

close(101)
close(102)

do i=1,nx
  print *, "(x",i,") =", x(i)
enddo

do i=1,6
  print *, "w(",i,") =", w(i) 
enddo
wsum=sum(w(1:6))
print *, "wsum =", wsum

call system("./bin/free-warp")

open(unit=103,file="Ct.out",status="old")
read(103,*)
read(103,*) (raux1(j),j=1,2)
f(1)=raux1(2)

close(103)

end !subroutine
