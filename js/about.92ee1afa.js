(window["webpackJsonp"]=window["webpackJsonp"]||[]).push([["about"],{"1e22":function(e,t,a){},"5bca":function(e,t,a){"use strict";var n=a("1e22"),i=a.n(n);i.a},"7d4c":function(e,t,a){"use strict";var n=a("a5ab"),i=a.n(n);i.a},"9e8a":function(e,t,a){"use strict";var n=a("dade"),i=a.n(n);i.a},a5ab:function(e,t,a){},bada:function(e,t,a){"use strict";var n=a("e78d"),i=a.n(n);i.a},dade:function(e,t,a){},e78d:function(e,t,a){},f2b4:function(e,t,a){"use strict";a.r(t);var n=function(){var e=this,t=e.$createElement,a=e._self._c||t;return a("v-container",{attrs:{fluid:""}},[a("v-form",{ref:"form"},[a("v-text-field",{attrs:{rules:e.rules,label:"Initial Seed",required:"",dark:"",dense:""},model:{value:e.mInitialSeed,callback:function(t){e.mInitialSeed=t},expression:"mInitialSeed"}}),a("v-btn",{staticClass:"mr-2",attrs:{disabled:!e.valid,dark:""},on:{click:e.generate}},[e._v("Generate")])],1),a("v-container",{staticClass:"table"},[a("v-data-table",{attrs:{headers:e.headers,items:e.mGameSeed,"items-per-page":20,"mobile-breakpoint":360,dark:"","hide-default-footer":"",dense:""}})],1)],1)},i=[],r=(a("a434"),a("bc01"),a("d3b7"),a("25f0"),a("d4ec")),s=a("bee2"),d=function(){function e(){Object(r["a"])(this,e)}return Object(s["a"])(e,[{key:"init",value:function(e){this.mSeed1=Math.imul(1812433253,e^e>>>30)+1>>>0,this.mSeed2=Math.imul(1812433253,this.mSeed1^this.mSeed1>>>30)+2>>>0,this.mSeed3=Math.imul(1812433253,this.mSeed2^this.mSeed2>>>30)+3>>>0,this.mSeed4=Math.imul(1812433253,this.mSeed3^this.mSeed3>>>30)+4>>>0}},{key:"getU32",value:function(){var e=(this.mSeed1^this.mSeed1<<11)>>>0;return this.mSeed1=this.mSeed2,this.mSeed2=this.mSeed3,this.mSeed3=this.mSeed4,this.mSeed4=(e^e>>>8^this.mSeed4^this.mSeed4>>>19)>>>0,this.mSeed4}}]),e}(),o={data:function(){return{valid:!0,rules:[function(e){return parseInt(e)<=4294967295&&0<=parseInt(e)||"Initial Seed must be number"}],mInitialSeed:0,mGameSeed:[],headers:[{text:"Type",value:"type",align:"center",sortable:!1},{text:"Initial Seed",value:"mSeed",align:"center",sortable:!1},{text:"mSeed1",value:"mSeed1",align:"center",sortable:!1},{text:"mSeed2",value:"mSeed2",align:"center",sortable:!1},{text:"mSeed3",value:"mSeed3",align:"center",sortable:!1},{text:"mSeed4",value:"mSeed4",align:"center",sortable:!1},{text:"getU32()",value:"mNumber",align:"center",sortable:!1}]}},methods:{generate:function(){this.mGameSeed.splice(0,this.mGameSeed.length);var e=new d;e.init(this.mInitialSeed);for(var t=[this.mInitialSeed,e.getU32(),e.getU32()],a=0;a<3;++a){e.init(t[a]);for(var n=0;n<5;++n)this.mGameSeed.push({type:"WAVE".concat(a+1),mSeed:t[a].toString(16).toUpperCase(),mSeed1:e.mSeed1.toString(16).toUpperCase(),mSeed2:e.mSeed2.toString(16).toUpperCase(),mSeed3:e.mSeed3.toString(16).toUpperCase(),mSeed4:e.mSeed4.toString(16).toUpperCase(),mNumber:"-"}),e.getU32()}}}},m=o,l=(a("9e8a"),a("5bca"),a("2877")),u=a("6544"),v=a.n(u),c=a("8336"),S=a("a523"),h=a("8fea"),f=a("4bd4"),b=a("8654"),p=Object(l["a"])(m,n,i,!1,null,"a05cb214",null);t["default"]=p.exports;v()(p,{VBtn:c["a"],VContainer:S["a"],VDataTable:h["a"],VForm:f["a"],VTextField:b["a"]})},f820:function(e,t,a){"use strict";a.r(t);var n=function(){var e=this,t=e.$createElement,a=e._self._c||t;return a("div",{staticClass:"about"},[a("v-container",{attrs:{fluid:""}},[a("h1",[e._v("What's SeedHack")]),a("p",[e._v("SeedHack is the best way to fix waves for Salmon Run in the Shoal. Please make sure the console applying SeedHack must be a host.")]),a("h1",[e._v("Contributors")]),a("ul",[a("li",[a("a",{attrs:{href:"https://twitter.com/shadowninja108"}},[e._v("shadowninja108")]),e._v(" - Expertise in Splatoon 2's inner workings ")]),a("li",[a("a",{attrs:{href:"https://twitter.com/container12345"}},[e._v("container12345")]),e._v(" - Reverse engineering for Game::Coop classes ")])]),a("h1",[e._v("Source Code")]),a("p",[e._v("Every source code is public on GitHub.")]),a("highlight-code",{attrs:{auto:""}},[a("pre",[e._v("      let rnd = new Random();\n      rnd.init(this.seed);\n\n      for (let wave = 0; wave < 3; ++wave) {\n        for (let event = 0, sum = 0; event < 7; ++event) {\n          if ((wave > 0) && (mWave.event[wave - 1] != 0) && (mWave.event[wave - 1] == event))\n            continue;\n          sum += mProb.event[event]\n          if ((rnd.getU32() * sum / Math.pow(2, 32)) < mProb.event[event])\n            mWave.event[wave] = event\n        }\n        for (let tide = 0, sum = 0; tide < 3; ++tide) {\n          if ((tide == 0) && (1 <= mWave.event[wave] && (mWave.event[wave] <= 3)))\n            continue;\n          sum += mProb.tide[tide];\n          if ((rnd.getU32() * sum / Math.pow(2, 32)) < mProb.tide[tide])\n            mWave.event[wave] == 6 ? mWave.tide[wave] = 0 : mWave.tide[wave] = tide\n        }\n      }\n    ")])])],1)],1)},i=[],r=(a("7d4c"),a("bada"),a("2877")),s=a("6544"),d=a.n(s),o=a("a523"),m={},l=Object(r["a"])(m,n,i,!1,null,"002a9300",null);t["default"]=l.exports;d()(l,{VContainer:o["a"]})}}]);