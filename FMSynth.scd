s.boot;


(
SynthDef(\FM,
    {
        arg p3 = 0.5, p4 = 1, p5 = 440, p7 = 0, p8 = 0, t_gate = 0;
        var env1, env2, modFr, out, p6;
        p6 = p5/3;
        env1 = EnvGen.kr(Env([0,p4,p4,0],[p3/5,(p3/5)*4,p3/10]),gate:t_gate);
        env2 = EnvGen.kr(Env([0,((p8-p7)*p6),((p8-p7)*p6),0],[p3/5,(p3/5)*4,p3/10]),gate:t_gate);



        modFr = SinOsc.kr(p6,0,env2+(p7*p6));
        out = SinOsc.ar(p5+modFr,0,env1);
        Out.ar(0,Pan2.ar(out,0));
    }
).add;
)

x = Synth(\FM);
x.set(\p5, 100 , \t_gate, 1);


n = NetAddr.new("127.0.0.1");

OSCFunc({|msg, time, addr, recvPort| x.set(\p5, msg[1], \t_gate, 1)}, '/FM/p5', n);


OSCFunc.trace(bool: true, hideStatusMsg: true);

//type1 (asr)
(
SynthDef(\FM1,
    {
        arg dur = 1, vol = 1, carr = 440, mInd1 = 4, mInd2 = 2, t_gate = 0, cmRatio = 3;
        var env1, env2, modFr, out, mf, temp;
        mf = carr/cmRatio;

		env1 = EnvGen.kr(Env([0,vol,vol,0],[dur/5,(dur/5)*4,dur/10]),gate:t_gate);
		env2 = EnvGen.kr(Env([0,((mInd2-mInd1)*mf),((mInd2-mInd1)*mf),0],[dur/5,(dur/5)*4,dur/10]),gate:t_gate);


        modFr = SinOsc.kr(mf,0,env2+(mInd1*mf));
        out = SinOsc.ar(carr+modFr,0,env1);
        Out.ar(0,Pan2.ar(out,0));
    }
).add;
)
//type2 (asdr)
(
SynthDef(\FM2,
    {
        arg dur = 1, vol = 1, carr = 440, mInd1 = 4, mInd2 = 2, t_gate = 0, cmRatio = 3;
        var env1, env2, modFr, out, mf, temp;
        mf = carr/cmRatio;

		env1 = EnvGen.kr(Env([0,vol,0.75*vol,0.75*vol,0],[dur/5,(dur/5)*4,dur/10]),gate:t_gate);
		env2 = EnvGen.kr(Env([0,((mInd2-mInd1)*mf),((mInd2-mInd1)*mf)*0.75,((mInd2-mInd1)*mf)*0.75,0],[dur/5,(dur/5)*4,dur/10]),gate:t_gate);


        modFr = SinOsc.kr(mf,0,env2+(mInd1*mf));
        out = SinOsc.ar(carr+modFr,0,env1);
        Out.ar(0,Pan2.ar(out,0));
    }
).add;
)
//type3 (perc)
(
SynthDef(\FM3,
    {
        arg dur = 1, vol = 1, carr = 440, mInd1 = 4, mInd2 = 2, t_gate = 0, cmRatio = 3;
        var env1, env2, modFr, out, mf, temp;
        mf = carr/cmRatio;

		env1 = EnvGen.kr(Env.perc(dur/4,dur*3/4,vol,-4.0),gate:t_gate);
		env2 = EnvGen.kr(Env.perc(dur/4,dur*3/4,((mInd2-mInd1)*mf),-4.0),gate:t_gate);

        modFr = SinOsc.kr(mf,0,env2+(mInd1*mf));
        out = SinOsc.ar(carr+modFr,0,env1);
        Out.ar(0,Pan2.ar(out,0));
    }
).add;
)

(

var envType = 1;
if(envType == 1,
	{
		x = Synth(\FM1);
		x.set(\carr,261.63,\t_gate,1);
		x.set(\carr,293.67,\t_gate,1);
		x.set(\carr,329.63,\t_gate,1);
	},{
		if(envType == 2,
			{
				x = Synth(\FM2);
				x.set(\carr,261.63,\t_gate,1);
				x.set(\carr,293.67,\t_gate,1);
				x.set(\carr,329.63,\t_gate,1);
			},{
				x = Synth(\FM3);
				x.set(\carr,261.63,\t_gate,1);
				x.set(\carr,293.67,\t_gate,1);
				x.set(\carr,329.63,\t_gate,1);
			}
		)
	}
)

)
