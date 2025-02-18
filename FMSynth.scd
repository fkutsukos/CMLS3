
Server.killAll;
s.boot;


//type1 (asr)
(
SynthDef(\FM1,
    {
        arg dur = 1, vol = 1, carr = 440, mInd1 = 4, mInd2 = 2, t_gate = 0, cmRatio = 3;
        var env1, env2, modFr, out, mf, temp;
        mf = carr/cmRatio;

		env1 = EnvGen.kr(Env([0,vol,vol,0],[0.1,dur-0.1,dur/10]),gate:t_gate);
		env2 = EnvGen.kr(Env([0,((mInd2-mInd1)*mf),((mInd2-mInd1)*mf),0],[0.1,dur-0.1,dur/10]),gate:t_gate);


        modFr = SinOsc.ar(mf,0,env2+(mInd1*mf));
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

		env1 = EnvGen.kr(Env([0,vol,0.75*vol,0.75*vol,0],[0.1,0.1,dur-0.3,0.1]),gate:t_gate);
		env2 = EnvGen.kr(Env([0,((mInd2-mInd1)*mf),((mInd2-mInd1)*mf)*0.75,((mInd2-mInd1)*mf)*0.75,0],[0.1,0.1,dur-0.3,0.1]),gate:t_gate);


        modFr = SinOsc.ar(mf,0,env2+(mInd1*mf));
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

        modFr = SinOsc.ar(mf,0,env2+(mInd1*mf));
        out = SinOsc.ar(carr+modFr,0,env1);
        Out.ar(0,Pan2.ar(out,0));
    }
).add;
)

(

~envType = 1;

x = Synth(\FM1);
y = Synth(\FM2);
z = Synth(\FM3);

n = NetAddr.new("127.0.0.1");

//listener for the envType
OSCFunc({|msg, time, addr, recvPort| ~envType = msg[1]}, '/FM/env', n);

//listeners for all the index
OSCFunc({|msg, time, addr, recvPort| if(~envType == 1,{x.set(\dur,msg[1])},{if(~envType == 2,{if(msg[1]>=0.3,{y.set(\dur,msg[1])},{y.set(\dur,0.3)})},{z.set(\dur,msg[1])})})}, '/FM/dur', n);
OSCFunc({|msg, time, addr, recvPort| if(~envType == 1,{x.set(\vol,msg[1]/100)},{if(~envType == 2,{y.set(\vol,msg[1]/100)},{z.set(\vol,msg[1]/100)})})}, '/FM/vol', n);
OSCFunc({|msg, time, addr, recvPort| if(~envType == 1,{x.set(\cmRatio,msg[1])},{if(~envType == 2,{y.set(\cmRatio,msg[1])},{z.set(\cmRatio,msg[1])})})}, '/FM/cmRatio', n);
OSCFunc({|msg, time, addr, recvPort| if(~envType == 1,{x.set(\mInd1,msg[1])},{if(~envType == 2,{y.set(\mInd1,msg[1])},{z.set(\mInd1,msg[1])})})}, '/FM/I1', n);
OSCFunc({|msg, time, addr, recvPort| if(~envType == 1,{x.set(\mInd2,msg[1])},{if(~envType == 2,{y.set(\mInd2,msg[1])},{z.set(\mInd2,msg[1])})})}, '/FM/I2', n);

//listener for playing the intruments
OSCFunc({|msg, time, addr, recvPort| if(~envType == 1,{x.set(\carr,msg[1] , \t_gate, 1)},{if(~envType == 2,{y.set(\carr,msg[1] ,  \t_gate, 1)},{z.set(\carr,msg[1] ,  \t_gate, 1)})})}, '/FM/carr', n);


OSCFunc.trace(bool: true, hideStatusMsg: true);

s.meter;
s.scope;
s.freqscope;

)