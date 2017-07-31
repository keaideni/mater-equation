#ifndef MASTER_H
#define MASTER_H
#include <complex>
#include <iostream>

using namespace std;

class master
{
private:
        complex<double> _phi1, _phi2;
        complex<double> _psi1, _psi2;
        complex<double> _rho1, _rho2;
public:
        const complex<double> phi1()const{return _phi1;};
        const complex<double> phi2()const{return _phi2;};
        const complex<double> psi1()const{return _psi1;};
        const complex<double> psi2()const{return _psi2;};
        const complex<double> rho1()const{return _rho1;};
        const complex<double> rho2()const{return _rho2;};



        master(const double& deltar, const double& deltaq, const double& j,
                const double& f, const double& kappa, const double& gamma):
        _phi1(1,0),
        _phi2(1,0),
        _psi1(1,0),
        _psi2(1,0),
        _rho1(1,0),
        _rho2(1,0)
        {
                complex<double> temphi1(_phi1), temphi2(_phi2), tempsi1(_psi1), tempsi2(_psi2);
                complex<double> temrho1(_rho1), temrho2(_rho2);
                complex<double> i(0,1);
                double deltat(0.0001);
                double err(1);int ii(0);


                while(err>0.000000001)
                {
                        _phi1+=(-i*(deltar*temphi1+tempsi1-j*temphi2+f)-kappa/2*temphi1)*deltat;
                        _phi2+=(-i*(deltar*temphi2+tempsi2-j*temphi1+f)-kappa/2*temphi2)*deltat;

                        _psi1+=(-i*(deltaq*tempsi1-temphi1*temrho1)-gamma/2*tempsi1)*deltat;
                        _psi2+=(-i*(deltaq*tempsi2-temphi2*temrho2)-gamma/2*tempsi2)*deltat;

                        _rho1+=(-i*2.0*(temphi1*conj(tempsi1)-conj(temphi1)*tempsi1)
                                -gamma*(temrho1+1.0))*deltat;
                        _rho2+=(-i*2.0*(temphi2*conj(tempsi2)-conj(temphi2)*tempsi2)
                                -gamma*(temrho2+1.0))*deltat;

                        err=abs(_phi1-temphi1)+abs(_phi2-temphi2)+abs(_psi1-tempsi1)+abs(_psi2-tempsi2)
                                +abs(_rho1-temrho1)+abs(_rho2-temrho2);

                        temphi1=_phi1;temphi2=_phi2;tempsi1=_psi1;tempsi2=_psi2;temrho1=_rho1;temrho2=_rho1;
                        //cout<<++ii<<"=>"<<err<<endl;

                }


        };
        ~master(){};
        
};



#endif // MASTER_H