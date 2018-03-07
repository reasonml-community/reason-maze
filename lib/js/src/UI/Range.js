'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Caml_format = require("bs-platform/lib/js/caml_format.js");
var ReasonReact = require("reason-react/lib/js/src/ReasonReact.js");

function si(prim) {
  return String(prim);
}

var component = ReasonReact.statelessComponent("Range");

function px(m) {
  return String(m) + "px";
}

function mkstyle(width, height, vertical) {
  var arg = /* Some */[String(height) + "px"];
  var arg$1 = /* Some */[String(width) + "px"];
  var style = function (param, param$1, param$2, param$3, param$4, param$5, param$6, param$7, param$8, param$9, param$10, param$11, param$12, param$13, param$14, param$15, param$16, param$17, param$18, param$19, param$20, param$21, param$22, param$23, param$24, param$25, param$26, param$27, param$28, param$29, param$30, param$31, param$32, param$33, param$34, param$35, param$36, param$37, param$38, param$39, param$40, param$41, param$42, param$43, param$44, param$45, param$46, param$47, param$48, param$49, param$50, param$51, param$52, param$53, param$54, param$55, param$56, param$57, param$58, param$59, param$60, param$61, param$62, param$63, param$64, param$65, param$66, param$67, param$68, param$69, param$70, param$71, param$72, param$73, param$74, param$75, param$76, param$77, param$78, param$79, param$80, param$81, param$82, param$83, param$84, param$85, param$86, param$87, param$88, param$89, param$90, param$91, param$92, param$93, param$94, param$95, param$96, param$97, param$98, param$99, param$100, param$101, param$102, param$103, param$104, param$105, param$106, param$107, param$108, param$109, param$110, param$111, param$112, param$113, param$114, param$115, param$116, param$117, param$118, param$119) {
    return (function (param$120, param$121, param$122, param$123, param$124, param$125, param$126, param$127, param$128, param$129, param$130, param$131, param$132, param$133, param$134, param$135, param$136, param$137, param$138, param$139, param$140, param$141, param$142, param$143, param$144, param$145, param$146, param$147, param$148, param$149, param$150, param$151, param$152, param$153, param$154, param$155, param$156, param$157, param$158, param$159, param$160, param$161, param$162, param$163, param$164, param$165, param$166, param$167, param$168, param$169, param$170, param$171, param$172, param$173, param$174, param$175, param$176, param$177, param$178, param$179, param$180, param$181, param$182, param$183, param$184, param$185, param$186, param$187, param$188, param$189, param$190, param$191, param$192, param$193, param$194, param$195, param$196, param$197, param$198, param$199, param$200, param$201, param$202, param$203, param$204, param$205, param$206, param$207, param$208, param$209, param$210, param$211, param$212, param$213, param$214, param$215, param$216, param$217, param$218, param$219, param$220, param$221, param$222, param$223, param$224, param$225, param$226, param$227, param$228, param$229, param$230, param$231, param$232, param$233, param$234, param$235, param$236, param$237, param$238, param$239, param$240, param$241, param$242, param$243, param$244, param$245, param$246, param$247, param$248, param$249, param$250, param$251, param$252, param$253, param$254, param$255, param$256, param$257, param$258, param$259, param$260, param$261, param$262, param$263, param$264, param$265, param$266, param$267, param$268, param$269, param$270, param$271, param$272, param$273, param$274, param$275, param$276, param$277, param$278, param$279, param$280, param$281, param$282, param$283, param$284, param$285, param$286, param$287, param$288, param$289, param$290, param$291, param$292, param$293, param$294, param$295, param$296, param$297, param$298, param$299, param$300, param$301, param$302, param$303, param$304, param$305, param$306, param$307, param$308, param$309, param$310, param$311, param$312, param$313, param$314, param$315, param$316, param$317, param$318, param$319, param$320, param$321, param$322, param$323, param$324, param$325, param$326, param$327, param$328, param$329, param$330, param$331, param$332, param$333, param$334, param$335, param$336, param$337, param$338, param$339, param$340, param$341, param$342, param$343, param$344, param$345) {
        var prim = param;
        var prim$1 = param$1;
        var prim$2 = param$2;
        var prim$3 = param$3;
        var prim$4 = param$4;
        var prim$5 = param$5;
        var prim$6 = param$6;
        var prim$7 = param$7;
        var prim$8 = param$8;
        var prim$9 = param$9;
        var prim$10 = param$10;
        var prim$11 = param$11;
        var prim$12 = param$12;
        var prim$13 = param$13;
        var prim$14 = param$14;
        var prim$15 = param$15;
        var prim$16 = param$16;
        var prim$17 = param$17;
        var prim$18 = param$18;
        var prim$19 = param$19;
        var prim$20 = param$20;
        var prim$21 = param$21;
        var prim$22 = param$22;
        var prim$23 = param$23;
        var prim$24 = param$24;
        var prim$25 = param$25;
        var prim$26 = param$26;
        var prim$27 = param$27;
        var prim$28 = param$28;
        var prim$29 = param$29;
        var prim$30 = param$30;
        var prim$31 = param$31;
        var prim$32 = param$32;
        var prim$33 = param$33;
        var prim$34 = param$34;
        var prim$35 = param$35;
        var prim$36 = param$36;
        var prim$37 = param$37;
        var prim$38 = param$38;
        var prim$39 = param$39;
        var prim$40 = param$40;
        var prim$41 = param$41;
        var prim$42 = param$42;
        var prim$43 = param$43;
        var prim$44 = param$44;
        var prim$45 = param$45;
        var prim$46 = param$46;
        var prim$47 = param$47;
        var prim$48 = param$48;
        var prim$49 = param$49;
        var prim$50 = param$50;
        var prim$51 = param$51;
        var prim$52 = param$52;
        var prim$53 = param$53;
        var prim$54 = arg;
        var prim$55 = param$54;
        var prim$56 = param$55;
        var prim$57 = param$56;
        var prim$58 = param$57;
        var prim$59 = param$58;
        var prim$60 = param$59;
        var prim$61 = param$60;
        var prim$62 = param$61;
        var prim$63 = param$62;
        var prim$64 = param$63;
        var prim$65 = param$64;
        var prim$66 = param$65;
        var prim$67 = param$66;
        var prim$68 = param$67;
        var prim$69 = param$68;
        var prim$70 = param$69;
        var prim$71 = param$70;
        var prim$72 = param$71;
        var prim$73 = param$72;
        var prim$74 = param$73;
        var prim$75 = param$74;
        var prim$76 = param$75;
        var prim$77 = param$76;
        var prim$78 = param$77;
        var prim$79 = param$78;
        var prim$80 = param$79;
        var prim$81 = param$80;
        var prim$82 = param$81;
        var prim$83 = param$82;
        var prim$84 = param$83;
        var prim$85 = param$84;
        var prim$86 = param$85;
        var prim$87 = param$86;
        var prim$88 = param$87;
        var prim$89 = param$88;
        var prim$90 = param$89;
        var prim$91 = param$90;
        var prim$92 = param$91;
        var prim$93 = param$92;
        var prim$94 = param$93;
        var prim$95 = param$94;
        var prim$96 = param$95;
        var prim$97 = param$96;
        var prim$98 = param$97;
        var prim$99 = param$98;
        var prim$100 = param$99;
        var prim$101 = param$100;
        var prim$102 = param$101;
        var prim$103 = param$102;
        var prim$104 = param$103;
        var prim$105 = param$104;
        var prim$106 = param$105;
        var prim$107 = param$106;
        var prim$108 = param$107;
        var prim$109 = param$108;
        var prim$110 = param$109;
        var prim$111 = param$110;
        var prim$112 = param$111;
        var prim$113 = param$112;
        var prim$114 = param$113;
        var prim$115 = param$114;
        var prim$116 = param$115;
        var prim$117 = param$116;
        var prim$118 = param$117;
        var prim$119 = param$118;
        var prim$120 = param$119;
        var prim$121 = arg$1;
        var prim$122 = param$120;
        var prim$123 = param$121;
        var prim$124 = param$122;
        var prim$125 = param$123;
        var prim$126 = param$124;
        var prim$127 = param$125;
        var prim$128 = param$126;
        var prim$129 = param$127;
        var prim$130 = param$128;
        var prim$131 = param$129;
        var prim$132 = param$130;
        var prim$133 = param$131;
        var prim$134 = param$132;
        var prim$135 = param$133;
        var prim$136 = param$134;
        var prim$137 = param$135;
        var prim$138 = param$136;
        var prim$139 = param$137;
        var prim$140 = param$138;
        var prim$141 = param$139;
        var prim$142 = param$140;
        var prim$143 = param$141;
        var prim$144 = param$142;
        var prim$145 = param$143;
        var prim$146 = param$144;
        var prim$147 = param$145;
        var prim$148 = param$146;
        var prim$149 = param$147;
        var prim$150 = param$148;
        var prim$151 = param$149;
        var prim$152 = param$150;
        var prim$153 = param$151;
        var prim$154 = param$152;
        var prim$155 = param$153;
        var prim$156 = param$154;
        var prim$157 = param$155;
        var prim$158 = param$156;
        var prim$159 = param$157;
        var prim$160 = param$158;
        var prim$161 = param$159;
        var prim$162 = param$160;
        var prim$163 = param$161;
        var prim$164 = param$162;
        var prim$165 = param$163;
        var prim$166 = param$164;
        var prim$167 = param$165;
        var prim$168 = param$166;
        var prim$169 = param$167;
        var prim$170 = param$168;
        var prim$171 = param$169;
        var prim$172 = param$170;
        var prim$173 = param$171;
        var prim$174 = param$172;
        var prim$175 = param$173;
        var prim$176 = param$174;
        var prim$177 = param$175;
        var prim$178 = param$176;
        var prim$179 = param$177;
        var prim$180 = param$178;
        var prim$181 = param$179;
        var prim$182 = param$180;
        var prim$183 = param$181;
        var prim$184 = param$182;
        var prim$185 = param$183;
        var prim$186 = param$184;
        var prim$187 = param$185;
        var prim$188 = param$186;
        var prim$189 = param$187;
        var prim$190 = param$188;
        var prim$191 = param$189;
        var prim$192 = param$190;
        var prim$193 = param$191;
        var prim$194 = param$192;
        var prim$195 = param$193;
        var prim$196 = param$194;
        var prim$197 = param$195;
        var prim$198 = param$196;
        var prim$199 = param$197;
        var prim$200 = param$198;
        var prim$201 = param$199;
        var prim$202 = param$200;
        var prim$203 = param$201;
        var prim$204 = param$202;
        var prim$205 = param$203;
        var prim$206 = param$204;
        var prim$207 = param$205;
        var prim$208 = param$206;
        var prim$209 = param$207;
        var prim$210 = param$208;
        var prim$211 = param$209;
        var prim$212 = param$210;
        var prim$213 = param$211;
        var prim$214 = param$212;
        var prim$215 = param$213;
        var prim$216 = param$214;
        var prim$217 = param$215;
        var prim$218 = param$216;
        var prim$219 = param$217;
        var prim$220 = param$218;
        var prim$221 = param$219;
        var prim$222 = param$220;
        var prim$223 = param$221;
        var prim$224 = param$222;
        var prim$225 = param$223;
        var prim$226 = param$224;
        var prim$227 = param$225;
        var prim$228 = param$226;
        var prim$229 = param$227;
        var prim$230 = param$228;
        var prim$231 = param$229;
        var prim$232 = param$230;
        var prim$233 = param$231;
        var prim$234 = param$232;
        var prim$235 = param$233;
        var prim$236 = param$234;
        var prim$237 = param$235;
        var prim$238 = param$236;
        var prim$239 = param$237;
        var prim$240 = param$238;
        var prim$241 = param$239;
        var prim$242 = param$240;
        var prim$243 = param$241;
        var prim$244 = param$242;
        var prim$245 = param$243;
        var prim$246 = param$244;
        var prim$247 = param$245;
        var prim$248 = param$246;
        var prim$249 = param$247;
        var prim$250 = param$248;
        var prim$251 = param$249;
        var prim$252 = param$250;
        var prim$253 = param$251;
        var prim$254 = param$252;
        var prim$255 = param$253;
        var prim$256 = param$254;
        var prim$257 = param$255;
        var prim$258 = param$256;
        var prim$259 = param$257;
        var prim$260 = param$258;
        var prim$261 = param$259;
        var prim$262 = param$260;
        var prim$263 = param$261;
        var prim$264 = param$262;
        var prim$265 = param$263;
        var prim$266 = param$264;
        var prim$267 = param$265;
        var prim$268 = param$266;
        var prim$269 = param$267;
        var prim$270 = param$268;
        var prim$271 = param$269;
        var prim$272 = param$270;
        var prim$273 = param$271;
        var prim$274 = param$272;
        var prim$275 = param$273;
        var prim$276 = param$274;
        var prim$277 = param$275;
        var prim$278 = param$276;
        var prim$279 = param$277;
        var prim$280 = param$278;
        var prim$281 = param$279;
        var prim$282 = param$280;
        var prim$283 = param$281;
        var prim$284 = param$282;
        var prim$285 = param$283;
        var prim$286 = param$284;
        var prim$287 = param$285;
        var prim$288 = param$286;
        var prim$289 = param$287;
        var prim$290 = param$288;
        var prim$291 = param$289;
        var prim$292 = param$290;
        var prim$293 = param$291;
        var prim$294 = param$292;
        var prim$295 = param$293;
        var prim$296 = param$294;
        var prim$297 = param$295;
        var prim$298 = param$296;
        var prim$299 = param$297;
        var prim$300 = param$298;
        var prim$301 = param$299;
        var prim$302 = param$300;
        var prim$303 = param$301;
        var prim$304 = param$302;
        var prim$305 = param$303;
        var prim$306 = param$304;
        var prim$307 = param$305;
        var prim$308 = param$306;
        var prim$309 = param$307;
        var prim$310 = param$308;
        var prim$311 = param$309;
        var prim$312 = param$310;
        var prim$313 = param$311;
        var prim$314 = param$312;
        var prim$315 = param$313;
        var prim$316 = param$314;
        var prim$317 = param$315;
        var prim$318 = param$316;
        var prim$319 = param$317;
        var prim$320 = param$318;
        var prim$321 = param$319;
        var prim$322 = param$320;
        var prim$323 = param$321;
        var prim$324 = param$322;
        var prim$325 = param$323;
        var prim$326 = param$324;
        var prim$327 = param$325;
        var prim$328 = param$326;
        var prim$329 = param$327;
        var prim$330 = param$328;
        var prim$331 = param$329;
        var prim$332 = param$330;
        var prim$333 = param$331;
        var prim$334 = param$332;
        var prim$335 = param$333;
        var prim$336 = param$334;
        var prim$337 = param$335;
        var prim$338 = param$336;
        var prim$339 = param$337;
        var prim$340 = param$338;
        var prim$341 = param$339;
        var prim$342 = param$340;
        var prim$343 = param$341;
        var prim$344 = param$342;
        var prim$345 = param$343;
        var prim$346 = param$344;
        var tmp = { };
        if (prim) {
          tmp.azimuth = prim[0];
        }
        if (prim$1) {
          tmp.background = prim$1[0];
        }
        if (prim$2) {
          tmp.backgroundAttachment = prim$2[0];
        }
        if (prim$3) {
          tmp.backgroundColor = prim$3[0];
        }
        if (prim$4) {
          tmp.backgroundImage = prim$4[0];
        }
        if (prim$5) {
          tmp.backgroundPosition = prim$5[0];
        }
        if (prim$6) {
          tmp.backgroundRepeat = prim$6[0];
        }
        if (prim$7) {
          tmp.border = prim$7[0];
        }
        if (prim$8) {
          tmp.borderCollapse = prim$8[0];
        }
        if (prim$9) {
          tmp.borderColor = prim$9[0];
        }
        if (prim$10) {
          tmp.borderSpacing = prim$10[0];
        }
        if (prim$11) {
          tmp.borderStyle = prim$11[0];
        }
        if (prim$12) {
          tmp.borderTop = prim$12[0];
        }
        if (prim$13) {
          tmp.borderRight = prim$13[0];
        }
        if (prim$14) {
          tmp.borderBottom = prim$14[0];
        }
        if (prim$15) {
          tmp.borderLeft = prim$15[0];
        }
        if (prim$16) {
          tmp.borderTopColor = prim$16[0];
        }
        if (prim$17) {
          tmp.borderRightColor = prim$17[0];
        }
        if (prim$18) {
          tmp.borderBottomColor = prim$18[0];
        }
        if (prim$19) {
          tmp.borderLeftColor = prim$19[0];
        }
        if (prim$20) {
          tmp.borderTopStyle = prim$20[0];
        }
        if (prim$21) {
          tmp.borderRightStyle = prim$21[0];
        }
        if (prim$22) {
          tmp.borderBottomStyle = prim$22[0];
        }
        if (prim$23) {
          tmp.borderLeftStyle = prim$23[0];
        }
        if (prim$24) {
          tmp.borderTopWidth = prim$24[0];
        }
        if (prim$25) {
          tmp.borderRightWidth = prim$25[0];
        }
        if (prim$26) {
          tmp.borderBottomWidth = prim$26[0];
        }
        if (prim$27) {
          tmp.borderLeftWidth = prim$27[0];
        }
        if (prim$28) {
          tmp.borderWidth = prim$28[0];
        }
        if (prim$29) {
          tmp.bottom = prim$29[0];
        }
        if (prim$30) {
          tmp.captionSide = prim$30[0];
        }
        if (prim$31) {
          tmp.clear = prim$31[0];
        }
        if (prim$32) {
          tmp.clip = prim$32[0];
        }
        if (prim$33) {
          tmp.color = prim$33[0];
        }
        if (prim$34) {
          tmp.content = prim$34[0];
        }
        if (prim$35) {
          tmp.counterIncrement = prim$35[0];
        }
        if (prim$36) {
          tmp.counterReset = prim$36[0];
        }
        if (prim$37) {
          tmp.cue = prim$37[0];
        }
        if (prim$38) {
          tmp.cueAfter = prim$38[0];
        }
        if (prim$39) {
          tmp.cueBefore = prim$39[0];
        }
        if (prim$40) {
          tmp.cursor = prim$40[0];
        }
        if (prim$41) {
          tmp.direction = prim$41[0];
        }
        if (prim$42) {
          tmp.display = prim$42[0];
        }
        if (prim$43) {
          tmp.elevation = prim$43[0];
        }
        if (prim$44) {
          tmp.emptyCells = prim$44[0];
        }
        if (prim$45) {
          tmp.float = prim$45[0];
        }
        if (prim$46) {
          tmp.font = prim$46[0];
        }
        if (prim$47) {
          tmp.fontFamily = prim$47[0];
        }
        if (prim$48) {
          tmp.fontSize = prim$48[0];
        }
        if (prim$49) {
          tmp.fontSizeAdjust = prim$49[0];
        }
        if (prim$50) {
          tmp.fontStretch = prim$50[0];
        }
        if (prim$51) {
          tmp.fontStyle = prim$51[0];
        }
        if (prim$52) {
          tmp.fontVariant = prim$52[0];
        }
        if (prim$53) {
          tmp.fontWeight = prim$53[0];
        }
        if (prim$54) {
          tmp.height = prim$54[0];
        }
        if (prim$55) {
          tmp.left = prim$55[0];
        }
        if (prim$56) {
          tmp.letterSpacing = prim$56[0];
        }
        if (prim$57) {
          tmp.lineHeight = prim$57[0];
        }
        if (prim$58) {
          tmp.listStyle = prim$58[0];
        }
        if (prim$59) {
          tmp.listStyleImage = prim$59[0];
        }
        if (prim$60) {
          tmp.listStylePosition = prim$60[0];
        }
        if (prim$61) {
          tmp.listStyleType = prim$61[0];
        }
        if (prim$62) {
          tmp.margin = prim$62[0];
        }
        if (prim$63) {
          tmp.marginTop = prim$63[0];
        }
        if (prim$64) {
          tmp.marginRight = prim$64[0];
        }
        if (prim$65) {
          tmp.marginBottom = prim$65[0];
        }
        if (prim$66) {
          tmp.marginLeft = prim$66[0];
        }
        if (prim$67) {
          tmp.markerOffset = prim$67[0];
        }
        if (prim$68) {
          tmp.marks = prim$68[0];
        }
        if (prim$69) {
          tmp.maxHeight = prim$69[0];
        }
        if (prim$70) {
          tmp.maxWidth = prim$70[0];
        }
        if (prim$71) {
          tmp.minHeight = prim$71[0];
        }
        if (prim$72) {
          tmp.minWidth = prim$72[0];
        }
        if (prim$73) {
          tmp.orphans = prim$73[0];
        }
        if (prim$74) {
          tmp.outline = prim$74[0];
        }
        if (prim$75) {
          tmp.outlineColor = prim$75[0];
        }
        if (prim$76) {
          tmp.outlineStyle = prim$76[0];
        }
        if (prim$77) {
          tmp.outlineWidth = prim$77[0];
        }
        if (prim$78) {
          tmp.overflow = prim$78[0];
        }
        if (prim$79) {
          tmp.overflowX = prim$79[0];
        }
        if (prim$80) {
          tmp.overflowY = prim$80[0];
        }
        if (prim$81) {
          tmp.padding = prim$81[0];
        }
        if (prim$82) {
          tmp.paddingTop = prim$82[0];
        }
        if (prim$83) {
          tmp.paddingRight = prim$83[0];
        }
        if (prim$84) {
          tmp.paddingBottom = prim$84[0];
        }
        if (prim$85) {
          tmp.paddingLeft = prim$85[0];
        }
        if (prim$86) {
          tmp.page = prim$86[0];
        }
        if (prim$87) {
          tmp.pageBreakAfter = prim$87[0];
        }
        if (prim$88) {
          tmp.pageBreakBefore = prim$88[0];
        }
        if (prim$89) {
          tmp.pageBreakInside = prim$89[0];
        }
        if (prim$90) {
          tmp.pause = prim$90[0];
        }
        if (prim$91) {
          tmp.pauseAfter = prim$91[0];
        }
        if (prim$92) {
          tmp.pauseBefore = prim$92[0];
        }
        if (prim$93) {
          tmp.pitch = prim$93[0];
        }
        if (prim$94) {
          tmp.pitchRange = prim$94[0];
        }
        if (prim$95) {
          tmp.playDuring = prim$95[0];
        }
        if (prim$96) {
          tmp.position = prim$96[0];
        }
        if (prim$97) {
          tmp.quotes = prim$97[0];
        }
        if (prim$98) {
          tmp.richness = prim$98[0];
        }
        if (prim$99) {
          tmp.right = prim$99[0];
        }
        if (prim$100) {
          tmp.size = prim$100[0];
        }
        if (prim$101) {
          tmp.speak = prim$101[0];
        }
        if (prim$102) {
          tmp.speakHeader = prim$102[0];
        }
        if (prim$103) {
          tmp.speakNumeral = prim$103[0];
        }
        if (prim$104) {
          tmp.speakPunctuation = prim$104[0];
        }
        if (prim$105) {
          tmp.speechRate = prim$105[0];
        }
        if (prim$106) {
          tmp.stress = prim$106[0];
        }
        if (prim$107) {
          tmp.tableLayout = prim$107[0];
        }
        if (prim$108) {
          tmp.textAlign = prim$108[0];
        }
        if (prim$109) {
          tmp.textDecoration = prim$109[0];
        }
        if (prim$110) {
          tmp.textIndent = prim$110[0];
        }
        if (prim$111) {
          tmp.textShadow = prim$111[0];
        }
        if (prim$112) {
          tmp.textTransform = prim$112[0];
        }
        if (prim$113) {
          tmp.top = prim$113[0];
        }
        if (prim$114) {
          tmp.unicodeBidi = prim$114[0];
        }
        if (prim$115) {
          tmp.verticalAlign = prim$115[0];
        }
        if (prim$116) {
          tmp.visibility = prim$116[0];
        }
        if (prim$117) {
          tmp.voiceFamily = prim$117[0];
        }
        if (prim$118) {
          tmp.volume = prim$118[0];
        }
        if (prim$119) {
          tmp.whiteSpace = prim$119[0];
        }
        if (prim$120) {
          tmp.widows = prim$120[0];
        }
        if (prim$121) {
          tmp.width = prim$121[0];
        }
        if (prim$122) {
          tmp.wordSpacing = prim$122[0];
        }
        if (prim$123) {
          tmp.zIndex = prim$123[0];
        }
        if (prim$124) {
          tmp.opacity = prim$124[0];
        }
        if (prim$125) {
          tmp.backgroundOrigin = prim$125[0];
        }
        if (prim$126) {
          tmp.backgroundSize = prim$126[0];
        }
        if (prim$127) {
          tmp.backgroundClip = prim$127[0];
        }
        if (prim$128) {
          tmp.borderRadius = prim$128[0];
        }
        if (prim$129) {
          tmp.borderTopLeftRadius = prim$129[0];
        }
        if (prim$130) {
          tmp.borderTopRightRadius = prim$130[0];
        }
        if (prim$131) {
          tmp.borderBottomLeftRadius = prim$131[0];
        }
        if (prim$132) {
          tmp.borderBottomRightRadius = prim$132[0];
        }
        if (prim$133) {
          tmp.borderImage = prim$133[0];
        }
        if (prim$134) {
          tmp.borderImageSource = prim$134[0];
        }
        if (prim$135) {
          tmp.borderImageSlice = prim$135[0];
        }
        if (prim$136) {
          tmp.borderImageWidth = prim$136[0];
        }
        if (prim$137) {
          tmp.borderImageOutset = prim$137[0];
        }
        if (prim$138) {
          tmp.borderImageRepeat = prim$138[0];
        }
        if (prim$139) {
          tmp.boxShadow = prim$139[0];
        }
        if (prim$140) {
          tmp.columns = prim$140[0];
        }
        if (prim$141) {
          tmp.columnCount = prim$141[0];
        }
        if (prim$142) {
          tmp.columnFill = prim$142[0];
        }
        if (prim$143) {
          tmp.columnGap = prim$143[0];
        }
        if (prim$144) {
          tmp.columnRule = prim$144[0];
        }
        if (prim$145) {
          tmp.columnRuleColor = prim$145[0];
        }
        if (prim$146) {
          tmp.columnRuleStyle = prim$146[0];
        }
        if (prim$147) {
          tmp.columnRuleWidth = prim$147[0];
        }
        if (prim$148) {
          tmp.columnSpan = prim$148[0];
        }
        if (prim$149) {
          tmp.columnWidth = prim$149[0];
        }
        if (prim$150) {
          tmp.breakAfter = prim$150[0];
        }
        if (prim$151) {
          tmp.breakBefore = prim$151[0];
        }
        if (prim$152) {
          tmp.breakInside = prim$152[0];
        }
        if (prim$153) {
          tmp.rest = prim$153[0];
        }
        if (prim$154) {
          tmp.restAfter = prim$154[0];
        }
        if (prim$155) {
          tmp.restBefore = prim$155[0];
        }
        if (prim$156) {
          tmp.speakAs = prim$156[0];
        }
        if (prim$157) {
          tmp.voiceBalance = prim$157[0];
        }
        if (prim$158) {
          tmp.voiceDuration = prim$158[0];
        }
        if (prim$159) {
          tmp.voicePitch = prim$159[0];
        }
        if (prim$160) {
          tmp.voiceRange = prim$160[0];
        }
        if (prim$161) {
          tmp.voiceRate = prim$161[0];
        }
        if (prim$162) {
          tmp.voiceStress = prim$162[0];
        }
        if (prim$163) {
          tmp.voiceVolume = prim$163[0];
        }
        if (prim$164) {
          tmp.objectFit = prim$164[0];
        }
        if (prim$165) {
          tmp.objectPosition = prim$165[0];
        }
        if (prim$166) {
          tmp.imageResolution = prim$166[0];
        }
        if (prim$167) {
          tmp.imageOrientation = prim$167[0];
        }
        if (prim$168) {
          tmp.alignContent = prim$168[0];
        }
        if (prim$169) {
          tmp.alignItems = prim$169[0];
        }
        if (prim$170) {
          tmp.alignSelf = prim$170[0];
        }
        if (prim$171) {
          tmp.flex = prim$171[0];
        }
        if (prim$172) {
          tmp.flexBasis = prim$172[0];
        }
        if (prim$173) {
          tmp.flexDirection = prim$173[0];
        }
        if (prim$174) {
          tmp.flexFlow = prim$174[0];
        }
        if (prim$175) {
          tmp.flexGrow = prim$175[0];
        }
        if (prim$176) {
          tmp.flexShrink = prim$176[0];
        }
        if (prim$177) {
          tmp.flexWrap = prim$177[0];
        }
        if (prim$178) {
          tmp.justifyContent = prim$178[0];
        }
        if (prim$179) {
          tmp.order = prim$179[0];
        }
        if (prim$180) {
          tmp.textDecorationColor = prim$180[0];
        }
        if (prim$181) {
          tmp.textDecorationLine = prim$181[0];
        }
        if (prim$182) {
          tmp.textDecorationSkip = prim$182[0];
        }
        if (prim$183) {
          tmp.textDecorationStyle = prim$183[0];
        }
        if (prim$184) {
          tmp.textEmphasis = prim$184[0];
        }
        if (prim$185) {
          tmp.textEmphasisColor = prim$185[0];
        }
        if (prim$186) {
          tmp.textEmphasisPosition = prim$186[0];
        }
        if (prim$187) {
          tmp.textEmphasisStyle = prim$187[0];
        }
        if (prim$188) {
          tmp.textUnderlinePosition = prim$188[0];
        }
        if (prim$189) {
          tmp.fontFeatureSettings = prim$189[0];
        }
        if (prim$190) {
          tmp.fontKerning = prim$190[0];
        }
        if (prim$191) {
          tmp.fontLanguageOverride = prim$191[0];
        }
        if (prim$192) {
          tmp.fontSynthesis = prim$192[0];
        }
        if (prim$193) {
          tmp.forntVariantAlternates = prim$193[0];
        }
        if (prim$194) {
          tmp.fontVariantCaps = prim$194[0];
        }
        if (prim$195) {
          tmp.fontVariantEastAsian = prim$195[0];
        }
        if (prim$196) {
          tmp.fontVariantLigatures = prim$196[0];
        }
        if (prim$197) {
          tmp.fontVariantNumeric = prim$197[0];
        }
        if (prim$198) {
          tmp.fontVariantPosition = prim$198[0];
        }
        if (prim$199) {
          tmp.all = prim$199[0];
        }
        if (prim$200) {
          tmp.glyphOrientationVertical = prim$200[0];
        }
        if (prim$201) {
          tmp.textCombineUpright = prim$201[0];
        }
        if (prim$202) {
          tmp.textOrientation = prim$202[0];
        }
        if (prim$203) {
          tmp.writingMode = prim$203[0];
        }
        if (prim$204) {
          tmp.shapeImageThreshold = prim$204[0];
        }
        if (prim$205) {
          tmp.shapeMargin = prim$205[0];
        }
        if (prim$206) {
          tmp.shapeOutside = prim$206[0];
        }
        if (prim$207) {
          tmp.clipPath = prim$207[0];
        }
        if (prim$208) {
          tmp.clipRule = prim$208[0];
        }
        if (prim$209) {
          tmp.mask = prim$209[0];
        }
        if (prim$210) {
          tmp.maskBorder = prim$210[0];
        }
        if (prim$211) {
          tmp.maskBorderMode = prim$211[0];
        }
        if (prim$212) {
          tmp.maskBorderOutset = prim$212[0];
        }
        if (prim$213) {
          tmp.maskBorderRepeat = prim$213[0];
        }
        if (prim$214) {
          tmp.maskBorderSlice = prim$214[0];
        }
        if (prim$215) {
          tmp.maskBorderSource = prim$215[0];
        }
        if (prim$216) {
          tmp.maskBorderWidth = prim$216[0];
        }
        if (prim$217) {
          tmp.maskClip = prim$217[0];
        }
        if (prim$218) {
          tmp.maskComposite = prim$218[0];
        }
        if (prim$219) {
          tmp.maskImage = prim$219[0];
        }
        if (prim$220) {
          tmp.maskMode = prim$220[0];
        }
        if (prim$221) {
          tmp.maskOrigin = prim$221[0];
        }
        if (prim$222) {
          tmp.maskPosition = prim$222[0];
        }
        if (prim$223) {
          tmp.maskRepeat = prim$223[0];
        }
        if (prim$224) {
          tmp.maskSize = prim$224[0];
        }
        if (prim$225) {
          tmp.maskType = prim$225[0];
        }
        if (prim$226) {
          tmp.backgroundBlendMode = prim$226[0];
        }
        if (prim$227) {
          tmp.isolation = prim$227[0];
        }
        if (prim$228) {
          tmp.mixBlendMode = prim$228[0];
        }
        if (prim$229) {
          tmp.boxDecorationBreak = prim$229[0];
        }
        if (prim$230) {
          tmp.boxSizing = prim$230[0];
        }
        if (prim$231) {
          tmp.caretColor = prim$231[0];
        }
        if (prim$232) {
          tmp.navDown = prim$232[0];
        }
        if (prim$233) {
          tmp.navLeft = prim$233[0];
        }
        if (prim$234) {
          tmp.navRight = prim$234[0];
        }
        if (prim$235) {
          tmp.navUp = prim$235[0];
        }
        if (prim$236) {
          tmp.outlineOffset = prim$236[0];
        }
        if (prim$237) {
          tmp.resize = prim$237[0];
        }
        if (prim$238) {
          tmp.textOverflow = prim$238[0];
        }
        if (prim$239) {
          tmp.grid = prim$239[0];
        }
        if (prim$240) {
          tmp.gridArea = prim$240[0];
        }
        if (prim$241) {
          tmp.gridAutoColumns = prim$241[0];
        }
        if (prim$242) {
          tmp.gridAutoFlow = prim$242[0];
        }
        if (prim$243) {
          tmp.gridAutoRows = prim$243[0];
        }
        if (prim$244) {
          tmp.gridColumn = prim$244[0];
        }
        if (prim$245) {
          tmp.gridColumnEnd = prim$245[0];
        }
        if (prim$246) {
          tmp.gridColumnGap = prim$246[0];
        }
        if (prim$247) {
          tmp.gridColumnStart = prim$247[0];
        }
        if (prim$248) {
          tmp.gridGap = prim$248[0];
        }
        if (prim$249) {
          tmp.gridRow = prim$249[0];
        }
        if (prim$250) {
          tmp.gridRowEnd = prim$250[0];
        }
        if (prim$251) {
          tmp.gridRowGap = prim$251[0];
        }
        if (prim$252) {
          tmp.gridRowStart = prim$252[0];
        }
        if (prim$253) {
          tmp.gridTemplate = prim$253[0];
        }
        if (prim$254) {
          tmp.gridTempalteAreas = prim$254[0];
        }
        if (prim$255) {
          tmp.gridTemplateColumns = prim$255[0];
        }
        if (prim$256) {
          tmp.gridTemplateRows = prim$256[0];
        }
        if (prim$257) {
          tmp.willChange = prim$257[0];
        }
        if (prim$258) {
          tmp.hangingPunctuation = prim$258[0];
        }
        if (prim$259) {
          tmp.hyphens = prim$259[0];
        }
        if (prim$260) {
          tmp.lineBreak = prim$260[0];
        }
        if (prim$261) {
          tmp.overflowWrap = prim$261[0];
        }
        if (prim$262) {
          tmp.tabSize = prim$262[0];
        }
        if (prim$263) {
          tmp.textAlignLast = prim$263[0];
        }
        if (prim$264) {
          tmp.textJustify = prim$264[0];
        }
        if (prim$265) {
          tmp.wordBreak = prim$265[0];
        }
        if (prim$266) {
          tmp.wordWrap = prim$266[0];
        }
        if (prim$267) {
          tmp.animation = prim$267[0];
        }
        if (prim$268) {
          tmp.animationDelay = prim$268[0];
        }
        if (prim$269) {
          tmp.animationDirection = prim$269[0];
        }
        if (prim$270) {
          tmp.animationDuration = prim$270[0];
        }
        if (prim$271) {
          tmp.animationFillMode = prim$271[0];
        }
        if (prim$272) {
          tmp.animationIterationCount = prim$272[0];
        }
        if (prim$273) {
          tmp.animationName = prim$273[0];
        }
        if (prim$274) {
          tmp.animationPlayState = prim$274[0];
        }
        if (prim$275) {
          tmp.animationTimingFunction = prim$275[0];
        }
        if (prim$276) {
          tmp.transition = prim$276[0];
        }
        if (prim$277) {
          tmp.transitionDelay = prim$277[0];
        }
        if (prim$278) {
          tmp.transitionDuration = prim$278[0];
        }
        if (prim$279) {
          tmp.transitionProperty = prim$279[0];
        }
        if (prim$280) {
          tmp.transitionTimingFunction = prim$280[0];
        }
        if (prim$281) {
          tmp.backfaceVisibility = prim$281[0];
        }
        if (prim$282) {
          tmp.perspective = prim$282[0];
        }
        if (prim$283) {
          tmp.perspectiveOrigin = prim$283[0];
        }
        if (prim$284) {
          tmp.transform = prim$284[0];
        }
        if (prim$285) {
          tmp.transformOrigin = prim$285[0];
        }
        if (prim$286) {
          tmp.transformStyle = prim$286[0];
        }
        if (prim$287) {
          tmp.justifyItems = prim$287[0];
        }
        if (prim$288) {
          tmp.justifySelf = prim$288[0];
        }
        if (prim$289) {
          tmp.placeContent = prim$289[0];
        }
        if (prim$290) {
          tmp.placeItems = prim$290[0];
        }
        if (prim$291) {
          tmp.placeSelf = prim$291[0];
        }
        if (prim$292) {
          tmp.appearance = prim$292[0];
        }
        if (prim$293) {
          tmp.caret = prim$293[0];
        }
        if (prim$294) {
          tmp.caretAnimation = prim$294[0];
        }
        if (prim$295) {
          tmp.caretShape = prim$295[0];
        }
        if (prim$296) {
          tmp.userSelect = prim$296[0];
        }
        if (prim$297) {
          tmp.maxLines = prim$297[0];
        }
        if (prim$298) {
          tmp.marqueeDirection = prim$298[0];
        }
        if (prim$299) {
          tmp.marqueeLoop = prim$299[0];
        }
        if (prim$300) {
          tmp.marqueeSpeed = prim$300[0];
        }
        if (prim$301) {
          tmp.marqueeStyle = prim$301[0];
        }
        if (prim$302) {
          tmp.overflowStyle = prim$302[0];
        }
        if (prim$303) {
          tmp.rotation = prim$303[0];
        }
        if (prim$304) {
          tmp.rotationPoint = prim$304[0];
        }
        if (prim$305) {
          tmp.alignmentBaseline = prim$305[0];
        }
        if (prim$306) {
          tmp.baselineShift = prim$306[0];
        }
        if (prim$307) {
          tmp.clip = prim$307[0];
        }
        if (prim$308) {
          tmp.clipPath = prim$308[0];
        }
        if (prim$309) {
          tmp.clipRule = prim$309[0];
        }
        if (prim$310) {
          tmp.colorInterpolation = prim$310[0];
        }
        if (prim$311) {
          tmp.colorInterpolationFilters = prim$311[0];
        }
        if (prim$312) {
          tmp.colorProfile = prim$312[0];
        }
        if (prim$313) {
          tmp.colorRendering = prim$313[0];
        }
        if (prim$314) {
          tmp.cursor = prim$314[0];
        }
        if (prim$315) {
          tmp.dominantBaseline = prim$315[0];
        }
        if (prim$316) {
          tmp.fill = prim$316[0];
        }
        if (prim$317) {
          tmp.fillOpacity = prim$317[0];
        }
        if (prim$318) {
          tmp.fillRule = prim$318[0];
        }
        if (prim$319) {
          tmp.filter = prim$319[0];
        }
        if (prim$320) {
          tmp.floodColor = prim$320[0];
        }
        if (prim$321) {
          tmp.floodOpacity = prim$321[0];
        }
        if (prim$322) {
          tmp.glyphOrientationHorizontal = prim$322[0];
        }
        if (prim$323) {
          tmp.glyphOrientationVertical = prim$323[0];
        }
        if (prim$324) {
          tmp.imageRendering = prim$324[0];
        }
        if (prim$325) {
          tmp.kerning = prim$325[0];
        }
        if (prim$326) {
          tmp.lightingColor = prim$326[0];
        }
        if (prim$327) {
          tmp.markerEnd = prim$327[0];
        }
        if (prim$328) {
          tmp.markerMid = prim$328[0];
        }
        if (prim$329) {
          tmp.markerStart = prim$329[0];
        }
        if (prim$330) {
          tmp.pointerEvents = prim$330[0];
        }
        if (prim$331) {
          tmp.shapeRendering = prim$331[0];
        }
        if (prim$332) {
          tmp.stopColor = prim$332[0];
        }
        if (prim$333) {
          tmp.stopOpacity = prim$333[0];
        }
        if (prim$334) {
          tmp.stroke = prim$334[0];
        }
        if (prim$335) {
          tmp.strokeDasharray = prim$335[0];
        }
        if (prim$336) {
          tmp.strokeDashoffset = prim$336[0];
        }
        if (prim$337) {
          tmp.strokeLinecap = prim$337[0];
        }
        if (prim$338) {
          tmp.strokeLinejoin = prim$338[0];
        }
        if (prim$339) {
          tmp.strokeMiterlimit = prim$339[0];
        }
        if (prim$340) {
          tmp.strokeOpacity = prim$340[0];
        }
        if (prim$341) {
          tmp.strokeWidth = prim$341[0];
        }
        if (prim$342) {
          tmp.textAnchor = prim$342[0];
        }
        if (prim$343) {
          tmp.textRendering = prim$343[0];
        }
        if (prim$344) {
          tmp.rubyAlign = prim$344[0];
        }
        if (prim$345) {
          tmp.rubyMerge = prim$345[0];
        }
        if (prim$346) {
          tmp.rubyPosition = prim$346[0];
        }
        return tmp;
      });
  };
  if (vertical !== 0) {
    return style(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */["rotate(-90deg)"], /* Some */[String(width / 2 | 0) + "px " + (String(width / 2 | 0) + "px")], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* () */0);
  } else {
    return style(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* () */0);
  }
}

function getValue(evt) {
  return Caml_format.caml_int_of_string(evt.target.value);
}

function make(min, max, value, step, width, height, vertical, onChange, _) {
  var newrecord = component.slice();
  newrecord[/* render */9] = (function () {
      return React.createElement("input", {
                  style: mkstyle(width, height, vertical),
                  max: String(max),
                  min: min,
                  step: step,
                  type: "range",
                  value: String(value),
                  onChange: (function (evt) {
                      return Curry._1(onChange, Caml_format.caml_int_of_string(evt.target.value));
                    })
                });
    });
  return newrecord;
}

exports.si = si;
exports.component = component;
exports.px = px;
exports.mkstyle = mkstyle;
exports.getValue = getValue;
exports.make = make;
/* component Not a pure module */
