/*
 * ThermocoupleMath.c
 *
 *  Created on: Jun 16, 2023
 *      Author: agapov
 */

#include "ThermocoupleMath.h"
#include "math.h"

/* Private function prototypes -----------------------------------------------*/
double Type_J_Thermocouple_direct(double degree);
double Type_J_Thermocouple_inverse(double microvolts);
double Type_K_Thermocouple_direct(double degree);
double Type_K_Thermocouple_inverse(double microvolts);
double Type_T_Thermocouple_direct(double degree);
double Type_T_Thermocouple_inverse(double microvolts);
double Type_E_Thermocouple_direct(double degree);
double Type_E_Thermocouple_inverse(double microvolts);
double Type_N_Thermocouple_direct(double degree);
double Type_N_Thermocouple_inverse(double microvolts);
double Type_B_Thermocouple_direct(double degree);
double Type_B_Thermocouple_inverse(double microvolts);
double Type_S_Thermocouple_direct(double degree);
double Type_S_Thermocouple_inverse(double microvolts);
double Type_R_Thermocouple_direct(double degree);
double Type_R_Thermocouple_inverse(double microvolts);
double Type_L_Thermocouple_direct(double degree);
double Type_L_Thermocouple_inverse(double microvolts);
double Type_M_Thermocouple_direct(double degree);
double Type_M_Thermocouple_inverse(double microvolts);
double Type_A1_Thermocouple_direct(double degree);
double Type_A1_Thermocouple_inverse(double microvolts);
double Type_A2_Thermocouple_direct(double degree);
double Type_A2_Thermocouple_inverse(double microvolts);
double Type_A3_Thermocouple_direct(double degree);
double Type_A3_Thermocouple_inverse(double microvolts);


double Thermocouple_direct(enum TC_Type type, double degree, double TXC_degree)
{
	switch(type)
	{
		case Type_J: 	return (Type_J_Thermocouple_direct(degree) - Type_J_Thermocouple_direct(TXC_degree));
		case Type_K: 	return (Type_K_Thermocouple_direct(degree) - Type_K_Thermocouple_direct(TXC_degree));
		case Type_E: 	return (Type_E_Thermocouple_direct(degree) - Type_E_Thermocouple_direct(TXC_degree));
		case Type_T: 	return (Type_T_Thermocouple_direct(degree) - Type_T_Thermocouple_direct(TXC_degree));
		case Type_N: 	return (Type_N_Thermocouple_direct(degree) - Type_N_Thermocouple_direct(TXC_degree));
		case Type_B: 	return (Type_B_Thermocouple_direct(degree) - Type_B_Thermocouple_direct(TXC_degree));
		case Type_S: 	return (Type_S_Thermocouple_direct(degree) - Type_S_Thermocouple_direct(TXC_degree));
		case Type_R: 	return (Type_R_Thermocouple_direct(degree) - Type_R_Thermocouple_direct(TXC_degree));
		case Type_L: 	return (Type_L_Thermocouple_direct(degree) - Type_L_Thermocouple_direct(TXC_degree));
		case Type_M: 	return (Type_M_Thermocouple_direct(degree) - Type_M_Thermocouple_direct(TXC_degree));
		case Type_A1: 	return (Type_A1_Thermocouple_direct(degree) - Type_A1_Thermocouple_direct(TXC_degree));
		case Type_A2: 	return (Type_A2_Thermocouple_direct(degree) - Type_A2_Thermocouple_direct(TXC_degree));
		case Type_A3: 	return (Type_A3_Thermocouple_direct(degree) - Type_A3_Thermocouple_direct(TXC_degree));
		default: return 0;
	}
}

double Thermocouple_inverse(enum TC_Type type, double microvolts, double TXC_degree)
{
	double TXC_microvolts = 0;
	switch(type)
	{
		case Type_J: 	TXC_microvolts = Type_J_Thermocouple_direct(TXC_degree);
						return Type_J_Thermocouple_inverse(microvolts + TXC_microvolts);
		case Type_K: 	TXC_microvolts = Type_K_Thermocouple_direct(TXC_degree);
						return Type_K_Thermocouple_inverse(microvolts + TXC_microvolts);
		case Type_E: 	TXC_microvolts = Type_E_Thermocouple_direct(TXC_degree);
						return Type_E_Thermocouple_inverse(microvolts + TXC_microvolts);
		case Type_T: 	TXC_microvolts = Type_T_Thermocouple_direct(TXC_degree);
						return Type_T_Thermocouple_inverse(microvolts + TXC_microvolts);
		case Type_N: 	TXC_microvolts = Type_N_Thermocouple_direct(TXC_degree);
						return Type_N_Thermocouple_inverse(microvolts + TXC_microvolts);
		case Type_B: 	TXC_microvolts = Type_B_Thermocouple_direct(TXC_degree);
						return Type_B_Thermocouple_inverse(microvolts + TXC_microvolts);
		case Type_S: 	TXC_microvolts = Type_S_Thermocouple_direct(TXC_degree);
						return Type_S_Thermocouple_inverse(microvolts + TXC_microvolts);
		case Type_R: 	TXC_microvolts = Type_R_Thermocouple_direct(TXC_degree);
						return Type_R_Thermocouple_inverse(microvolts + TXC_microvolts);
		case Type_L: 	TXC_microvolts = Type_L_Thermocouple_direct(TXC_degree);
						return Type_L_Thermocouple_inverse(microvolts + TXC_microvolts);
		case Type_M: 	TXC_microvolts = Type_M_Thermocouple_direct(TXC_degree);
						return Type_M_Thermocouple_inverse(microvolts + TXC_microvolts);
		case Type_A1: 	TXC_microvolts = Type_A1_Thermocouple_direct(TXC_degree);
						return Type_A1_Thermocouple_inverse(microvolts + TXC_microvolts);
		case Type_A2: 	TXC_microvolts = Type_A2_Thermocouple_direct(TXC_degree);
						return Type_A2_Thermocouple_inverse(microvolts + TXC_microvolts);
		case Type_A3: 	TXC_microvolts = Type_A3_Thermocouple_direct(TXC_degree);
						return Type_A3_Thermocouple_inverse(microvolts + TXC_microvolts);
		default: return 0;
	}
}


/* Private variables ---------------------------------------------------------*/
struct ThermocoupleMath Thermocouple = {
	Type_J_Thermocouple_direct,
	Type_J_Thermocouple_inverse,
	Type_K_Thermocouple_direct,
	Type_K_Thermocouple_inverse,
	Type_T_Thermocouple_direct,
	Type_T_Thermocouple_inverse,
	Type_E_Thermocouple_direct,
	Type_E_Thermocouple_inverse,
	Type_N_Thermocouple_direct,
	Type_N_Thermocouple_inverse,
	Type_B_Thermocouple_direct,
	Type_B_Thermocouple_inverse,
	Type_S_Thermocouple_direct,
	Type_S_Thermocouple_inverse,
	Type_R_Thermocouple_direct,
	Type_R_Thermocouple_inverse,
	Type_L_Thermocouple_direct,
	Type_L_Thermocouple_inverse,
	Type_M_Thermocouple_direct,
	Type_M_Thermocouple_inverse,
	Type_A1_Thermocouple_direct,
	Type_A1_Thermocouple_inverse,
	Type_A2_Thermocouple_direct,
	Type_A2_Thermocouple_inverse,
	Type_A3_Thermocouple_direct,
	Type_A3_Thermocouple_inverse,
	Thermocouple_direct,
	Thermocouple_inverse
};

const double Type_R_Thermocouple_m50to1064p18_direct_C[10] = {0.0, 5.28961729765, 1.39166589782e-2, -2.38855693017e-5, 3.56916001063e-8, -4.62347666298e-11, 5.00777441034e-14, -3.73105886191e-17, 1.57716482367e-20, -2.81038625251e-24};
const double Type_R_Thermocouple_1064p18to1664p5_direct_C[6] = {2.95157925316e3, -2.52061251332, 1.59564501865e-2, -7.64085947576e-6, 2.05305291024e-9, -2.93359668173e-13};
const double Type_R_Thermocouple_1664p5to1768p1_direct_C[5] = {1.52232118209e5, -2.68819888545e2, 1.71280280471e-1, -3.45895706453e-5, -9.34633971046e-12};
const double Type_R_Thermocouple_m226to1923_inverse_C[11] = {0.0, 1.8891380e-1, -9.3835290e-5, 1.3068619e-7, -2.2703580e-10, 3.5145659e-13, -3.8953900e-16, 2.8239471e-19, -1.2607281e-22, 3.1353611e-26, -3.3187769e-30};
const double Type_R_Thermocouple_1923to11361_inverse_C[10] = {1.334584505e1, 1.472644573e-1, -1.844024844e-5, 4.031129726e-9, -6.249428360e-13, 6.468412046e-17, -4.458750426e-21, 1.994710146e-25, -5.313401790e-30, 6.481976217e-35};
const double Type_R_Thermocouple_11361to19739_inverse_C[6] = {-8.199599416e1, 1.553962042e-1, -8.342197663e-6, 4.279433549e-10, -1.191577910e-14, 1.492290091e-19};
const double Type_R_Thermocouple_19739to21103_inverse_C[5] = {3.406177836e4, -7.023729171, 5.582903813e-4, -1.952394635e-8, 2.560740231e-13};
const double Type_J_Thermocouple_m210to760_direct_C[9] = {0.0, 5.0381187815e1, 3.0475836930e-2, -8.5681065720e-5, 1.3228195295e-7, -1.7052958337e-10, 2.0948090697e-13, -1.2538395336e-16, 1.5631725697e-20};
const double Type_J_Thermocouple_760to1200_direct_C[6] = {2.9645625681e5, -1.4976127786e3, 3.1787103924, -3.1847686701e-3, 1.5720819004e-6, -3.0691369056e-10};
const double Type_J_Thermocouple_m8095to0_inverse_C[9] = {0.0, 1.9528268e-2, -1.2286185e-6, -1.0752178e-9, -5.9086933e-13, -1.7256713e-16, -2.8131513e-20, -2.3963370e-24, -8.3823321e-29};
const double Type_J_Thermocouple_0to42919_inverse_C[8] = {0.0, 1.978425e-2, -2.001204e-7, 1.036969e-11, -2.549687e-16, 3.585153e-21, -5.344285e-26, 5.099890e-31};
const double Type_J_Thermocouple_42919to69553_inverse_C[6] = {-3.11358187e3, 3.00543684e-1, -9.94773230e-6, 1.70276630e-10, -1.43033468e-15, 4.73886084e-21};
const double Type_K_Thermocouple_m270to0_direct_C[11] = {0.0, 3.9450128025e1, 2.3622373598e-2, -3.2858906784e-4, -4.9904828777e-6, -6.7509059173e-8, -5.7410327428e-10, -3.1088872894e-12, -1.0451609365e-14, -1.9889266878e-17, -1.6322697486e-20};
const double Type_K_Thermocouple_0to1372_direct_C[10] = {-1.7600413686e1,3.8921204975e1,1.8558770032e-2,-9.9457592874e-5,3.1840945719e-7,-5.6072844889e-10,5.6075059059e-13,-3.2020720003e-16,9.7151147152e-20,-1.2104721275e-23};
const double Type_K_Thermocouple_m5891to0_inverse_C[10] = {0.0,2.5173462e-2,-1.1662878e-6,-1.0833638e-9,-8.9773540e-13,-3.7342377e-16,-8.6632643e-20,-1.0450598e-23,-5.1920577e-28,-1.052755e-35};
const double Type_K_Thermocouple_0to20644_inverse_C[9] = {0.0,2.508355e-2,7.860106e-8,-2.503131e-10,8.315270e-14,-1.228034e-17,9.804036e-22,-4.413030e-26,1.057734e-30};
const double Type_K_Thermocouple_20644to54886_inverse_C[7] = {-1.318058e2,4.830222e-2,-1.646031e-6,5.464731e-11,-9.650715e-16,8.802193e-21,-3.110810e-26};
const double Type_T_Thermocouple_m270to0_direct_C[15] = {0.0, 3.8748106364e1, 4.4194434347e-2, 1.1844323105e-4, 2.0032973554e-5, 9.0138019559e-7, 2.2651156593e-8, 3.6071154205e-10, 3.8493939883e-12, 2.8213521925e-14, 1.4251594779e-16, 4.8768662286e-19, 1.0795539270e-21, 1.3945027062e-24, 7.9795153927e-28};
const double Type_T_Thermocouple_0to1000_direct_C[9] = {0.0, 3.8748106364e1, 3.3292227880e-2, 2.0618243404e-4, -2.1882256846e-6, 1.0996880928e-8, -3.0815758772e-11, 4.5479135290e-14, -2.7512901673e-17};
const double Type_T_Thermocouple_m5603to0_inverse_C[8] = {0.0, 2.5949192e-2, -2.1316967e-7, 7.9018692e-10, 4.2527777e-13, 1.3304473e-16, 2.0241446e-20, 1.2668171e-24};
const double Type_T_Thermocouple_0to20872_inverse_C[7] = {0.0, 2.592800e-2, -7.602961e-7, 4.637791e-11, -2.165394e-15, 6.048144e-20, -7.293422e-25};
const double Type_E_Thermocouple_m270to0_direct_C[14] = {0.0, 5.8665508708e1, 4.5410977124e-2, -7.7998048686e-4, -2.5800160843e-5, -5.9452583057e-7, -9.3214058667e-9, -1.0287605534e-10, -8.0370123621e-13, -4.3979497391e-15, -1.6414776355e-17, -3.9673619516e-20, -5.5827328721e-23, -3.4657842013e-26};
const double Type_E_Thermocouple_0to400_direct_C[11] = {0.0, 5.8665508710e1, 4.5032275582e-2, 2.8908407212e-5, -3.3056896652e-7, 6.5024403270e-10, -1.9197495504e-13, -1.2536600497e-15, 2.1489217569e-18, -1.4388041782e-21, 3.5960899481e-25};
const double Type_E_Thermocouple_m8825to0_inverse_C[9] = {0.0, 1.6977288e-2, -4.3514970e-7, -1.5859697e-10, -9.2502871e-14, -2.6084314e-17, -4.1360199e-21, -3.4034030e-25, -1.1564890e-29};
const double Type_E_Thermocouple_0to76373_inverse_C[10] = {0.0, 1.7057035e-2, -2.3301759e-7, 6.5435585e-12, -7.3562749e-17, -1.7896001e-21, 8.4036165e-26, -1.3735879e-30, 1.0629823e-35, -3.2447087e-41};
const double Type_N_Thermocouple_m270to0_direct_C[11] = {0.0, 2.6159105962e1, 1.0957484228e-2, -9.3841111554e-5, -4.6412039759e-8, -2.6303357716e-9, -2.2653438003e-11, -7.6089300791e-14, -9.3419667835e-17, 2.0849229339e-22, -3.0682196151e-26};
const double Type_N_Thermocouple_m270to1300_direct_C[11] = {0.0, 2.5929394601e1, 1.5710141880e-2, 4.3825627237e-5, -2.5261169794e-7, 6.4311819339e-10, -1.0063471519e-12, 9.9745338992e-16, -6.0863245607e-19};
const double Type_N_Thermocouple_m3990to0_inverse_C[10] = {0.0, 3.8436847e-2, 1.1010485e-6, 5.2229312e-9, 7.2060525e-12, 5.8488586e-15, 2.7754916e-18, 7.7075166e-22, 1.1582665e-25, 7.3138868e-30};
const double Type_N_Thermocouple_0to20613_inverse_C[8] = {0.0, 3.86896e-2, -1.08267e-6, 4.70205e-11, -2.12169e-18, -1.17272e-19, 5.39280e-24, -7.98156e-29};
const double Type_N_Thermocouple_20613to47513_inverse_C[6] = {1.972485e1, 3.300943e-2, -3.915159e-7, 9.855391e-12, -1.274371e-16, 7.767022e-22};
const double Type_N_Thermocouple_0to47513_inverse_C[9] = {0.0, 3.8783277e-2, -1.1612344e-6, 6.9525655e-11, -3.0090077e-15, 8.8311584e-20, -1.6213839e-24, 1.6693362e-29, -7.3117540e-35};
const double Type_B_Thermocouple_0to630p615_direct_C[7] = {0.0, -2.4650818346e-1, 5.9040421171e-3, -1.3257931636e-6, 1.5668291901e-9, -1.6944529240e-12, 6.2290347094e-16};
const double Type_B_Thermocouple_630p615to1820_direct_C[9] = {-3.8938168621e3, 2.8571747470e1, -8.4885104785e-2, 1.5785280164e-4, -1.6835344864e-7, 1.1109794013e-10, -4.4515431033e-14, 9.8975640821e-18, -9.3791330289e-22};
const double Type_B_Thermocouple_291to2431_inverse_C[9] = {9.8423321e1, 6.9971500e-1, -8.4765304e-4, 1.0052644e-6, -8.3345952e-10, 4.5508542e-13, -1.5523037e-16, 2.9886750e-20, -2.4742860e-24};
const double Type_B_Thermocouple_2431to13820_inverse_C[9] = {2.1315071e2, 2.8510504e-1, -5.2742887e-5, 9.9160804e-9, -1.2965303e-12, 1.1195870e-16, -6.0625199e-21, 1.8661696e-25, -2.4878585e-30};
const double Type_S_Thermocouple_m50to1064p18_direct_C[9] = {0.0, 5.40313308631, 1.25934289740e-2, -2.32477968689e-5, 3.22028823036e-8, -3.31465196389e-11, 2.55744251786e-14, -1.25068871393e-17, 2.71443176145e-21};
const double Type_S_Thermocouple_1064p18to1664p5_direct_C[5] = {1.32900445085e3, 3.34509311344, 6.54805192818e-3, -1.64856259209e-6, 1.29989605174e-11};
const double Type_S_Thermocouple_1664p5to1768p1_direct_C[5] = {1.46628232636e5, -2.58430516752e2, 1.63693574641e-1, -3.30439046987e-5, -9.43223690612e-12};
const double Type_S_Thermocouple_m235to1874_inverse_C[10] = {0.0, 1.84949460e-1, -8.00504062e-5, 1.02237430e-7, -1.52248592e-10, 1.88821343e-13, -1.59085941e-16, 8.23027880e-20, -2.34181944e-23, 2.79786260e-27};
const double Type_S_Thermocouple_1874to10332_inverse_C[10] = {1.291507177e1, 1.466298863e-1, -1.534713402e-5, 3.145945973e-9, -4.163257839e-13, 3.187963771e-17, -1.291637500e-21, 2.183475087e-26, -1.447379511e-31, 8.211272125e-36};
const double Type_S_Thermocouple_10332to17536_inverse_C[6] = {-8.087801117e1, 1.621573104e-1, -8.536869453e-6, 4.719686976e-10, -1.441693666e-14, 2.081618890e-19};
const double Type_S_Thermocouple_17536to18693_inverse_C[5] = {5.333875126e4, -1.235892298e1, 1.092657613e-3, -4.265693686e-8, 6.247205420e-13};
const double Type_A1_Thermocouple_0to2500_direct_C[9] = { 7.1564735e-1,1.1951905e1,1.6672625e-2,-2.8287807e-5,2.8397839e-8,-1.8505007e-11,7.3632123e-15,-1.6148878e-18,1.4901679e-22};
const double Type_A1_Thermocouple_0to33640_inverse_C[9] = { 0.9643027e3, 7.9495086e4, -4.9990310e3, 0.6341776e3, -4.7440967e1, 2.1811337, -5.8324228e-2, 8.2433725e-4, -4.5928480e-6};
const double Type_A2_Thermocouple_0to1800_direct_C[9] = {-1.0850558e-1, 1.1642292e1, 2.1280289e-2, -4.4258402e-5, 5.5652058e-8, -4.3801310e-11, 2.0228390e-14, -4.9354041e-18, 4.8119846e-22};
const double Type_A2_Thermocouple_0to27232_inverse_C[9] = {1.1196428e3, 8.0569397e4, -6.2279122e3, 0.9337015e3, -8.2608051e1, 4.4110979, -1.3610551e-1, 2.2183851e-3, -1.4527698e-5};
const double Type_A3_Thermocouple_0to1800_direct_C[9] = { -1.0649133e-1, 1.1686475e1, 1.8022157e-2, -3.3436998e-5, 3.7081688e-8, -2.5748444e-11, 1.0301893e-14, -2.0735944e-18, 1.4678450e-22};
const double Type_A3_Thermocouple_0to26773_inverse_C[9] = {0.8769216e3, 8.1483231e4, -5.9344173e3, 0.8699340e3, -7.6797687e1, 4.1814387, -1.3439670e-1, 2.342409e-3, -1.6988727e-5};
const double Type_L_Thermocouple_200to0_direct_C[9] = {-5.8952244e-2, 6.3391502e1, 6.7592964e-2, 2.0672566e-4, 5.5720884e-6, 5.7133860e-8, 3.2995593e-10, 9.9232420e-13, 1.2079584e-15};
const double Type_L_Thermocouple_0to800_direct_C[9] = {-1.8656953e-2, 6.3310975e1, 6.0153091e-2, -8.0073134e-5, 9.6946071e-8, -3.6047289e-11, -2.4694775e-13, 4.2880341e-16, -2.0725297e-19};
const double Type_L_Thermocouple_m9488to0_inverse_C[10] = {1.1573067e-1, 1.5884573e4, 4.0458554e1, 0.3170064e3, 0.1666128e3, 5.1946958e1, 9.5288883, 1.0301283e1, 6.0654431e-2, 1.5131878e-3};
const double Type_L_Thermocouple_0to66466_inverse_C[10] = {7.2069422, 1.5775525e4, -0.2261183e3, 9.4286756, -3.5394655e-1, 1.0050886e-2, -1.9323678e-4, 2.3816891e-6, -1.7130654e-8, 5.4857331e-11};
const double Type_M_Thermocouple_m200to100_direct_C[4] = {2.4455560e-3, 4.2638917e1, 5.0348392e-2, -4.4974485e-5};
const double Type_M_Thermocouple_m6154to4722_inverse_C[4] = {0.4548090e3, 2.2657698e1, -7.7935652e-4, 1.1786931e-7};







//---------------------------------------------------------------------------------------------
// 									Type_L direct
//---------------------------------------------------------------------------------------------
double Type_L_Thermocouple_200to0_direct(double degree)
{
	double RES = 0;
	for(int i=0;i<9;i++) RES += pow(degree, i)*Type_L_Thermocouple_200to0_direct_C[i];
	return RES;
}

double Type_L_Thermocouple_0to800_direct(double degree)
{
	double RES = 0;
	for(int i=0;i<9;i++) RES += pow(degree, i)*Type_L_Thermocouple_0to800_direct_C[i];
	return RES;
}


double Type_L_Thermocouple_direct(double degree)
{
	if(degree==0)return 0;
	else if(degree<0) return Type_L_Thermocouple_200to0_direct(degree);
	else return Type_L_Thermocouple_0to800_direct(degree);
}

//---------------------------------------------------------------------------------------------
// 									Type_L inverse
//---------------------------------------------------------------------------------------------
double Type_L_Thermocouple_m9488to0_inverse(double microvolts)
{
	double RES = 0;
	for(int i=0;i<10;i++) RES += pow(microvolts, i)*Type_L_Thermocouple_m9488to0_inverse_C[i];
	return RES;
}

double Type_L_Thermocouple_0to66466_inverse(double microvolts)
{
	double RES = 0;
	for(int i=0;i<10;i++) RES += pow(microvolts, i)*Type_L_Thermocouple_0to66466_inverse_C[i];
	return RES;
}


double Type_L_Thermocouple_inverse(double microvolts)
{
	if(microvolts==0)return 0;
	else if(microvolts<0) return Type_L_Thermocouple_m9488to0_inverse(microvolts);
	else return Type_L_Thermocouple_0to66466_inverse(microvolts);
}

//---------------------------------------------------------------------------------------------
// 									Type_M direct
//---------------------------------------------------------------------------------------------
double Type_M_Thermocouple_direct(double degree)
{
	double RES = 0;
	if(degree==0) return 0;
	else
	{
		for(int i=0;i<4;i++) RES += pow(degree, i)*Type_M_Thermocouple_m200to100_direct_C[i];
		return RES;
	}
}

//---------------------------------------------------------------------------------------------
// 									Type_M inverse
//---------------------------------------------------------------------------------------------
double Type_M_Thermocouple_inverse(double microvolts)
{
	double RES = 0;
	if(microvolts==0)return 0;
	else
	{
		for(int i=0;i<4;i++) RES += pow(microvolts, i)*Type_M_Thermocouple_m6154to4722_inverse_C[i];
		return RES;
	}
}

//---------------------------------------------------------------------------------------------
// 									Type_A3 direct
//---------------------------------------------------------------------------------------------
double Type_A3_Thermocouple_direct(double degree)
{
	double RES = 0;
	if(degree==0)return 0;
	else
	{
		for(int i=0;i<9;i++) RES += pow(degree, i)*Type_A3_Thermocouple_0to1800_direct_C[i];
		return RES;
	}
}

//---------------------------------------------------------------------------------------------
// 									Type_A3 inverse
//---------------------------------------------------------------------------------------------
double Type_A3_Thermocouple_inverse(double microvolts)
{
	double RES = 0;
	if(microvolts==0)return 0;
	else
	{
		for(int i=0;i<9;i++) RES += pow(microvolts, i)*Type_A3_Thermocouple_0to26773_inverse_C[i];
		return RES;
	}
}


//---------------------------------------------------------------------------------------------
// 									Type_A2 direct
//---------------------------------------------------------------------------------------------
double Type_A2_Thermocouple_direct(double degree)
{
	double RES = 0;
	if(degree==0)return 0;
	else
	{
		for(int i=0;i<9;i++) RES += pow(degree, i)*Type_A2_Thermocouple_0to1800_direct_C[i];
		return RES;
	}
}

//---------------------------------------------------------------------------------------------
// 									Type_A2 inverse
//---------------------------------------------------------------------------------------------
double Type_A2_Thermocouple_inverse(double microvolts)
{
	double RES = 0;
	if(microvolts==0)return 0;
	else
	{
		for(int i=0;i<9;i++) RES += pow(microvolts, i)*Type_A2_Thermocouple_0to27232_inverse_C[i];
		return RES;
	}
}

//---------------------------------------------------------------------------------------------
// 									Type_A1 direct
//---------------------------------------------------------------------------------------------
double Type_A1_Thermocouple_direct(double degree)
{
	double RES = 0;
	if(degree==0)return 0;
	else
	{
		for(int i=0;i<9;i++) RES += pow(degree, i)*Type_A1_Thermocouple_0to2500_direct_C[i];
		return RES;
	}
}

//---------------------------------------------------------------------------------------------
// 									Type_A1 inverse
//---------------------------------------------------------------------------------------------
double Type_A1_Thermocouple_inverse(double microvolts)
{
	double RES = 0;
	if(microvolts==0)return 0;
	else
	{
		for(int i=0;i<9;i++) RES += pow(microvolts, i)*Type_A1_Thermocouple_0to33640_inverse_C[i];
		return RES;
	}
}

//---------------------------------------------------------------------------------------------
// 									Type_T direct
//---------------------------------------------------------------------------------------------
double Type_T_Thermocouple_m270to0_direct(double degree)
{
	double RES = 0;
	for(int i=0;i<15;i++) RES += pow(degree, i)*Type_T_Thermocouple_m270to0_direct_C[i];
	return RES;
}

double Type_T_Thermocouple_0to1000_direct(double degree)
{
	double RES = 0;
	for(int i=0;i<9;i++) RES += pow(degree, i)*Type_T_Thermocouple_0to1000_direct_C[i];
	return RES;
}


double Type_T_Thermocouple_direct(double degree)
{
	if(degree==0)return 0;
	else if(degree<0) return Type_T_Thermocouple_m270to0_direct(degree);
	else return Type_T_Thermocouple_0to1000_direct(degree);
}

//---------------------------------------------------------------------------------------------
// 									Type_T inverse
//---------------------------------------------------------------------------------------------
double Type_T_Thermocouple_m5603to0_inverse(double microvolts)
{
	double RES = 0;
	for(int i=0;i<8;i++) RES += pow(microvolts, i)*Type_T_Thermocouple_m5603to0_inverse_C[i];
	return RES;
}

double Type_T_Thermocouple_0to20872_inverse(double microvolts)
{
	double RES = 0;
	for(int i=0;i<7;i++) RES += pow(microvolts, i)*Type_T_Thermocouple_0to20872_inverse_C[i];
	return RES;
}


double Type_T_Thermocouple_inverse(double microvolts)
{
	if(microvolts==0)return 0;
	else if(microvolts<0) return Type_T_Thermocouple_m5603to0_inverse(microvolts);
	else return Type_T_Thermocouple_0to20872_inverse(microvolts);
}


//---------------------------------------------------------------------------------------------
// 									Type_N direct
//---------------------------------------------------------------------------------------------
double Type_E_Thermocouple_m270to0_direct(double degree)
{
	double RES = 0;
	for(int i=0;i<14;i++) RES += pow(degree, i)*Type_E_Thermocouple_m270to0_direct_C[i];
	return RES;
}

double Type_E_Thermocouple_0to400_direct(double degree)
{
	double RES = 0;
	for(int i=0;i<11;i++) RES += pow(degree, i)*Type_E_Thermocouple_0to400_direct_C[i];
	return RES;
}


double Type_E_Thermocouple_direct(double degree)
{
	if(degree==0)return 0;
	else if(degree<0) return Type_E_Thermocouple_m270to0_direct(degree);
	else return Type_E_Thermocouple_0to400_direct(degree);
}

//---------------------------------------------------------------------------------------------
// 									Type_N inverse
//---------------------------------------------------------------------------------------------
double Type_E_Thermocouple_m8825to0_inverse(double microvolts)
{
	double RES = 0;
	for(int i=0;i<9;i++) RES += pow(microvolts, i)*Type_E_Thermocouple_m8825to0_inverse_C[i];
	return RES;
}

double Type_E_Thermocouple_0to76373_inverse(double microvolts)
{
	double RES = 0;
	for(int i=0;i<10;i++) RES += pow(microvolts, i)*Type_E_Thermocouple_0to76373_inverse_C[i];
	return RES;
}


double Type_E_Thermocouple_inverse(double microvolts)
{
	if(microvolts==0)return 0;
	else if(microvolts<0) return Type_E_Thermocouple_m8825to0_inverse(microvolts);
	else return Type_E_Thermocouple_0to76373_inverse(microvolts);
}



//---------------------------------------------------------------------------------------------
// 									Type_N direct
//---------------------------------------------------------------------------------------------
double Type_N_Thermocouple_m270to0_direct(double degree)
{
	double RES = 0;
	for(int i=0;i<11;i++) RES += pow(degree, i)*Type_N_Thermocouple_m270to0_direct_C[i];
	return RES;
}

double Type_N_Thermocouple_m270to1300_direct(double degree)
{
	double RES = 0;
	for(int i=0;i<11;i++) RES += pow(degree, i)*Type_N_Thermocouple_m270to1300_direct_C[i];
	return RES;
}


double Type_N_Thermocouple_direct(double degree)
{
	if(degree==0)return 0;
	else if(degree<0) return Type_N_Thermocouple_m270to0_direct(degree);
	else return Type_N_Thermocouple_m270to1300_direct(degree);
}

//---------------------------------------------------------------------------------------------
// 									Type_N inverse
//---------------------------------------------------------------------------------------------
double Type_N_Thermocouple_m3990to0_inverse(double microvolts)
{
	double RES = 0;
	for(int i=0;i<10;i++) RES += pow(microvolts, i)*Type_N_Thermocouple_m3990to0_inverse_C[i];
	return RES;
}

double Type_N_Thermocouple_0to20613_inverse(double microvolts)
{
	double RES = 0;
	for(int i=0;i<8;i++) RES += pow(microvolts, i)*Type_N_Thermocouple_0to20613_inverse_C[i];
	return RES;
}

double Type_N_Thermocouple_20613to47513_inverse(double microvolts)
{
	double RES = 0;
	for(int i=0;i<6;i++) RES += pow(microvolts, i)*Type_N_Thermocouple_20613to47513_inverse_C[i];
	return RES;
}

double Type_N_Thermocouple_inverse(double microvolts)
{
	if(microvolts==0)return 0;
	else if(microvolts<0) return Type_N_Thermocouple_m3990to0_inverse(microvolts);
	else if(microvolts<20613) return Type_N_Thermocouple_0to20613_inverse(microvolts);
	else return Type_N_Thermocouple_20613to47513_inverse(microvolts);
}



//---------------------------------------------------------------------------------------------
// 									Type_B direct
//---------------------------------------------------------------------------------------------
double Type_B_Thermocouple_0to630p615_direct(double degree)
{
	double RES = 0;
	for(int i=0;i<7;i++) RES += pow(degree, i)*Type_B_Thermocouple_0to630p615_direct_C[i];
	return RES;
}

double Type_B_Thermocouple_630p615to1820_direct(double degree)
{
	double RES = 0;
	for(int i=0;i<9;i++) RES += pow(degree, i)*Type_B_Thermocouple_630p615to1820_direct_C[i];
	return RES;
}


double Type_B_Thermocouple_direct(double degree)
{
	if(degree==0)return 0;
	else if(degree<630.615) return Type_B_Thermocouple_0to630p615_direct(degree);
	else return Type_B_Thermocouple_630p615to1820_direct(degree);
}

//---------------------------------------------------------------------------------------------
// 									Type_B inverse
//---------------------------------------------------------------------------------------------
double Type_B_Thermocouple_291to2431_inverse(double microvolts)
{
	double RES = 0;
	for(int i=0;i<9;i++) RES += pow(microvolts, i)*Type_B_Thermocouple_291to2431_inverse_C[i];
	return RES;
}

double Type_B_Thermocouple_2431to13820_inverse(double microvolts)
{
	double RES = 0;
	for(int i=0;i<9;i++) RES += pow(microvolts, i)*Type_B_Thermocouple_2431to13820_inverse_C[i];
	return RES;
}


double Type_B_Thermocouple_inverse(double microvolts)
{
	if(microvolts==0)return 0;
	else if(microvolts<2431) return Type_B_Thermocouple_291to2431_inverse(microvolts);
	else return Type_B_Thermocouple_2431to13820_inverse(microvolts);
}



//---------------------------------------------------------------------------------------------
// 									Type_S direct
//---------------------------------------------------------------------------------------------
double Type_S_Thermocouple_m50to1064p18_direct(double degree)
{
	double RES = 0;
	for(int i=0;i<9;i++) RES += pow(degree, i)*Type_S_Thermocouple_m50to1064p18_direct_C[i];
	return RES;
}

double Type_S_Thermocouple_1064p18to1664p5_direct(double degree)
{
	double RES = 0;
	for(int i=0;i<5;i++) RES += pow(degree, i)*Type_S_Thermocouple_1064p18to1664p5_direct_C[i];
	return RES;
}

double Type_S_Thermocouple_1664p5to1768p1_direct(double degree)
{
	double RES = 0;
	for(int i=0;i<5;i++) RES += pow(degree, i)*Type_S_Thermocouple_1664p5to1768p1_direct_C[i];
	return RES;
}

double Type_S_Thermocouple_direct(double degree)
{
	if(degree==0)return 0;
	else if(degree<1064.18) return Type_S_Thermocouple_m50to1064p18_direct(degree);
	if(degree<1664.5) return Type_S_Thermocouple_1064p18to1664p5_direct(degree);
	else return Type_S_Thermocouple_1664p5to1768p1_direct(degree);
}

//---------------------------------------------------------------------------------------------
// 									Type_S inverse
//---------------------------------------------------------------------------------------------
double Type_S_Thermocouple_m235to1874_inverse(double microvolts)
{
	double RES = 0;
	for(int i=0;i<10;i++) RES += pow(microvolts, i)*Type_S_Thermocouple_m235to1874_inverse_C[i];
	return RES;
}

double Type_S_Thermocouple_1874to10332_inverse(double microvolts)
{
	double RES = 0;
	for(int i=0;i<10;i++) RES += pow(microvolts, i)*Type_S_Thermocouple_1874to10332_inverse_C[i];
	return RES;
}

double Type_S_Thermocouple_10332to17536_inverse(double microvolts)
{
	double RES = 0;
	for(int i=0;i<6;i++) RES += pow(microvolts, i)*Type_S_Thermocouple_10332to17536_inverse_C[i];
	return RES;
}

double Type_S_Thermocouple_17536to18693_inverse(double microvolts)
{
	double RES = 0;
	for(int i=0;i<5;i++) RES += pow(microvolts, i)*Type_S_Thermocouple_17536to18693_inverse_C[i];
	return RES;
}

double Type_S_Thermocouple_inverse(double microvolts)
{
	if(microvolts==0)return 0;
	else if(microvolts<1874) return Type_S_Thermocouple_m235to1874_inverse(microvolts);
	else if(microvolts<10332) return Type_S_Thermocouple_1874to10332_inverse(microvolts);
	else if(microvolts<17536) return Type_S_Thermocouple_10332to17536_inverse(microvolts);
	else return Type_S_Thermocouple_17536to18693_inverse(microvolts);
}



//---------------------------------------------------------------------------------------------
// 									Type_R direct
//---------------------------------------------------------------------------------------------
double Type_R_Thermocouple_m50to1064p18_direct(double degree)
{
	double RES = 0;
	for(int i=0;i<10;i++) RES += pow(degree, i)*Type_R_Thermocouple_m50to1064p18_direct_C[i];
	return RES;
}

double Type_R_Thermocouple_1064p18to1664p5_direct(double degree)
{
	double RES = 0;
	for(int i=0;i<6;i++) RES += pow(degree, i)*Type_R_Thermocouple_1064p18to1664p5_direct_C[i];
	return RES;
}

double Type_R_Thermocouple_1664p5to1768p1_direct(double degree)
{
	double RES = 0;
	for(int i=0;i<5;i++) RES += pow(degree, i)*Type_R_Thermocouple_1664p5to1768p1_direct_C[i];
	return RES;
}

double Type_R_Thermocouple_direct(double degree)
{
	if(degree==0)return 0;
	else if(degree<1064.18) return Type_R_Thermocouple_m50to1064p18_direct(degree);
	if(degree<1664.5) return Type_R_Thermocouple_1064p18to1664p5_direct(degree);
	else return Type_R_Thermocouple_1664p5to1768p1_direct(degree);
}

//---------------------------------------------------------------------------------------------
// 									Type_R inverse
//---------------------------------------------------------------------------------------------
double Type_R_Thermocouple_m226to1923_inverse(double microvolts)
{
	double RES = 0;
	for(int i=0;i<11;i++) RES += pow(microvolts, i)*Type_R_Thermocouple_m226to1923_inverse_C[i];
	return RES;
}

double Type_R_Thermocouple_1923to11361_inverse(double microvolts)
{
	double RES = 0;
	for(int i=0;i<10;i++) RES += pow(microvolts, i)*Type_R_Thermocouple_1923to11361_inverse_C[i];
	return RES;
}

double Type_R_Thermocouple_11361to19739_inverse(double microvolts)
{
	double RES = 0;
	for(int i=0;i<6;i++) RES += pow(microvolts, i)*Type_R_Thermocouple_11361to19739_inverse_C[i];
	return RES;
}

double Type_R_Thermocouple_19739to21103_inverse(double microvolts)
{
	double RES = 0;
	for(int i=0;i<5;i++) RES += pow(microvolts, i)*Type_R_Thermocouple_19739to21103_inverse_C[i];
	return RES;
}

double Type_R_Thermocouple_inverse(double microvolts)
{
	if(microvolts==0)return 0;
	else if(microvolts<1923) return Type_R_Thermocouple_m226to1923_inverse(microvolts);
	else if(microvolts<11361) return Type_R_Thermocouple_1923to11361_inverse(microvolts);
	else if(microvolts<19739) return Type_R_Thermocouple_11361to19739_inverse(microvolts);
	else return Type_R_Thermocouple_19739to21103_inverse(microvolts);
}


//---------------------------------------------------------------------------------------------
// 									Type_J direct
//---------------------------------------------------------------------------------------------
double Type_J_Thermocouple_m210to760_direct(double degree)
{
	double RES = 0;
	for(int i=0;i<9;i++) RES += pow(degree, i)*Type_J_Thermocouple_m210to760_direct_C[i];
	return RES;
}

double Type_J_Thermocouple_760to1200_direct(double degree)
{
	double RES = 0;
	for(int i=0;i<6;i++) RES += pow(degree, i)*Type_J_Thermocouple_760to1200_direct_C[i];
	return RES;
}

double Type_J_Thermocouple_direct(double degree)
{
	if(degree==0)return 0;
	else if(degree<760) return Type_J_Thermocouple_m210to760_direct(degree);
	else return Type_J_Thermocouple_760to1200_direct(degree);
}

//---------------------------------------------------------------------------------------------
// 									Type_J inverse
//---------------------------------------------------------------------------------------------
double Type_J_Thermocouple_m8095to0_inverse(double microvolts)
{
	double RES = 0;
	for(int i=0;i<9;i++) RES += pow(microvolts, i)*Type_J_Thermocouple_m8095to0_inverse_C[i];
	return RES;
}

double Type_J_Thermocouple_0to42919_inverse(double microvolts)
{
	double RES = 0;
	for(int i=0;i<8;i++) RES += pow(microvolts, i)*Type_J_Thermocouple_0to42919_inverse_C[i];
	return RES;
}

double Type_J_Thermocouple_42919to69553_inverse(double microvolts)
{
	double RES = 0;
	for(int i=0;i<6;i++) RES += pow(microvolts, i)*Type_J_Thermocouple_42919to69553_inverse_C[i];
	return RES;
}

double Type_J_Thermocouple_inverse(double microvolts)
{
	if(microvolts==0)return 0;
	else if(microvolts<0) return Type_J_Thermocouple_m8095to0_inverse(microvolts);
	else if(microvolts<42919) return Type_J_Thermocouple_0to42919_inverse(microvolts);
	else return Type_J_Thermocouple_42919to69553_inverse(microvolts);
}

//---------------------------------------------------------------------------------------------
// 									Type_K direct
//---------------------------------------------------------------------------------------------
double Type_K_Thermocouple_m270to0_direct(double degree)
{
	double RES = 0;
	for(int i=0;i<11;i++) RES += pow(degree, i)*Type_K_Thermocouple_m270to0_direct_C[i];
	return RES;
}

double Type_K_Thermocouple_0to1372_direct(double degree)
{
	double RES = 0;
	double  C0 = 1.185976e2;
	double  C1 = -1.183432e-4;
	RES = C0*pow(2.71828, C1*(degree-126.9686)*(degree-126.9686));

	for(int i=0;i<10;i++) RES += pow(degree, i)*Type_K_Thermocouple_0to1372_direct_C[i];
	return RES;
}


double Type_K_Thermocouple_direct(double degree)
{
	if(degree==0)return 0;
	else if(degree<0) return Type_K_Thermocouple_m270to0_direct(degree);
	else return Type_K_Thermocouple_0to1372_direct(degree);
}

//---------------------------------------------------------------------------------------------
// 									Type_K inverse
//---------------------------------------------------------------------------------------------
double Type_K_Thermocouple_m5891to0_inverse(double microvolts)
{
	double RES = 0;
	for(int i=0;i<10;i++) RES += pow(microvolts, i)*Type_K_Thermocouple_m5891to0_inverse_C[i];
	return RES;
}

double Type_K_Thermocouple_0to20644_inverse(double microvolts)
{
	double RES = 0;
	for(int i=0;i<9;i++) RES += pow(microvolts, i)*Type_K_Thermocouple_0to20644_inverse_C[i];
	return RES;
}

double Type_K_Thermocouple_20644to54886_inverse(double microvolts)
{
	double RES = 0;
	for(int i=0;i<7;i++) RES += pow(microvolts, i)*Type_K_Thermocouple_20644to54886_inverse_C[i];
	return RES;
}

double Type_K_Thermocouple_inverse(double microvolts)
{
	if(microvolts==0)return 0;
	else if(microvolts<0) return Type_K_Thermocouple_m5891to0_inverse(microvolts);
	else if(microvolts<20644) return Type_K_Thermocouple_0to20644_inverse(microvolts);
	else return Type_K_Thermocouple_20644to54886_inverse(microvolts);
}



