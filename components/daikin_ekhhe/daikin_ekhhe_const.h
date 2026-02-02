#pragma once

#include <string>

namespace esphome {
namespace daikin_ekhhe {

// Define names as static constants
// this should match what is in const.py on the Python side
static const std::string A_LOW_WAT_T_PROBE       = "sonde_temp_eau_basse";
static const std::string B_UP_WAT_T_PROBE        = "sonde_temp_eau_haute";
static const std::string C_DEFROST_T_PROBE       = "sonde_température_de_dégivrage";
static const std::string D_SUPPLY_AIR_T_PROBE    = "sonde_temp_air_souffle";
static const std::string E_EVA_INLET_T_PROBE     = "sonde de temperature du gaz à l'entree de l'evaporateur";
static const std::string F_EVA_OUTLET_T_PROBE    = "sonde de temperature du gaz à la sortie de l'evaporateur";
static const std::string G_COMP_GAS_T_PROBE      = "sonde de temperature du gaz de refoulement du compresseur";
static const std::string H_SOLAR_T_PROBE         = "sonde de temperature pour capteur solaire";
static const std::string I_EEV_STEP              = "ouverture_etape_EEV";
static const std::string J_POWER_FW_VERSION      = "version_du_micrologiciel_carte_alimentation";
static const std::string L_UI_FW_VERSION         = "version du micrologiciel de l'interface utilisateur";

static const std::string DIG1_CONFIG             = "dig1_config";
static const std::string DIG2_CONFIG             = "dig2_config";
static const std::string DIG3_CONFIG             = "dig3_config";

static const std::string POWER_STATUS            = "etat_d'alimentation";
static const std::string OPERATIONAL_MODE        = "mode_fonctionnement";
static const std::string CURRENT_TIME            = "heure_actuelle";

static const std::string AUTO_T_TEMPERATURE      = "température_mode_automatique";
static const std::string ECO_T_TEMPERATURE       = "température_mode_eco";
static const std::string BOOST_T_TEMPERATURE     = "température_mode_boost";
static const std::string ELECTRIC_T_TEMPERATURE  = "température_mode_electric";

static const std::string P3_ANTL_SET_T           = "température de consigne anti-légionellose";
static const std::string P4_ANTL_DURATION        = "durée_antilégionelle";

}  // namespace daikin_ekhhe
}  // namespace esphome



