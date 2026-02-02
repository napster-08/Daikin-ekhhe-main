import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import number
from esphome.const import (
    CONF_ID,
    CONF_MIN_VALUE,
    CONF_MAX_VALUE,
    CONF_STEP,
    CONF_UNIT_OF_MEASUREMENT,
    CONF_DEVICE_CLASS,
)
from esphome.const import (
    CONF_ID,
    ICON_EMPTY,
    UNIT_EMPTY,
    UNIT_CELSIUS,
    UNIT_HOUR,
    UNIT_SECOND,
    UNIT_PERCENT,
    UNIT_MINUTE,
    DEVICE_CLASS_TEMPERATURE,
    DEVICE_CLASS_DURATION,
    DEVICE_CLASS_TIMESTAMP,
    STATE_CLASS_MEASUREMENT,
    STATE_CLASS_TOTAL_INCREASING,
    ENTITY_CATEGORY_DIAGNOSTIC,
    ENTITY_CATEGORY_NONE
)


from . import (
    CONF_EKHHE_ID,
    DaikinEkhhe,
    daikin_ekhhe_ns,
)

from .const import *

DaikinEkhheNumber = daikin_ekhhe_ns.class_(
    "DaikinEkhheNumber", number.Number, cg.Component
)


TYPES = [
    P3_ANTL_SET_T,
    P4_ANTL_DURATION,
    AUTO_T_TEMPERATURE,
    ECO_T_TEMPERATURE,
    BOOST_T_TEMPERATURE,
    ELECTRIC_T_TEMPERATURE,
]

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.Optional(P3_ANTL_SET_T): number.number_schema(DaikinEkhheNumber).extend({
                cv.GenerateID(): cv.declare_id(DaikinEkhheNumber),
                cv.Optional(CONF_MAX_VALUE, default=75): cv.float_,
                cv.Optional(CONF_MIN_VALUE, default=50): cv.float_,
                cv.Optional(CONF_STEP, default=1): cv.positive_float,
                cv.Optional(CONF_DEVICE_CLASS, default=DEVICE_CLASS_TEMPERATURE): cv.string,
                cv.Optional(CONF_UNIT_OF_MEASUREMENT, default=UNIT_CELSIUS): cv.string,
            }), 
            cv.Optional(P4_ANTL_DURATION): number.number_schema(DaikinEkhheNumber).extend({
                cv.GenerateID(): cv.declare_id(DaikinEkhheNumber),
                cv.Optional(CONF_MAX_VALUE, default=90): cv.float_,
                cv.Optional(CONF_MIN_VALUE, default=0): cv.float_,
                cv.Optional(CONF_STEP, default=1): cv.positive_float,
                cv.Optional(CONF_DEVICE_CLASS, default=DEVICE_CLASS_DURATION): cv.string,
                cv.Optional(CONF_UNIT_OF_MEASUREMENT, default=UNIT_MINUTE): cv.string,
            }), 
            cv.Optional(ECO_T_TEMPERATURE): number.number_schema(DaikinEkhheNumber).extend({
                cv.GenerateID(): cv.declare_id(DaikinEkhheNumber),
                cv.Optional(CONF_MAX_VALUE, default=62): cv.float_,
                cv.Optional(CONF_MIN_VALUE, default=43): cv.float_,
                cv.Optional(CONF_STEP, default=1): cv.positive_float,
                cv.Optional(CONF_DEVICE_CLASS, default=DEVICE_CLASS_TEMPERATURE): cv.string,
                cv.Optional(CONF_UNIT_OF_MEASUREMENT, default=UNIT_CELSIUS): cv.string,
            }),
            cv.Optional(AUTO_T_TEMPERATURE): number.number_schema(DaikinEkhheNumber).extend({
                cv.GenerateID(): cv.declare_id(DaikinEkhheNumber),
                cv.Optional(CONF_MAX_VALUE, default=62): cv.float_,
                cv.Optional(CONF_MIN_VALUE, default=43): cv.float_,
                cv.Optional(CONF_STEP, default=1): cv.positive_float,
                cv.Optional(CONF_DEVICE_CLASS, default=DEVICE_CLASS_TEMPERATURE): cv.string,
                cv.Optional(CONF_UNIT_OF_MEASUREMENT, default=UNIT_CELSIUS): cv.string,
            }),
            cv.Optional(BOOST_T_TEMPERATURE): number.number_schema(DaikinEkhheNumber).extend({
                cv.GenerateID(): cv.declare_id(DaikinEkhheNumber),
                cv.Optional(CONF_MAX_VALUE, default=75): cv.float_,
                cv.Optional(CONF_MIN_VALUE, default=43): cv.float_,
                cv.Optional(CONF_STEP, default=1): cv.positive_float,
                cv.Optional(CONF_DEVICE_CLASS, default=DEVICE_CLASS_TEMPERATURE): cv.string,
                cv.Optional(CONF_UNIT_OF_MEASUREMENT, default=UNIT_CELSIUS): cv.string,
            }),
            cv.Optional(ELECTRIC_T_TEMPERATURE): number.number_schema(DaikinEkhheNumber).extend({
                cv.GenerateID(): cv.declare_id(DaikinEkhheNumber),
                cv.Optional(CONF_MAX_VALUE, default=75): cv.float_,
                cv.Optional(CONF_MIN_VALUE, default=43): cv.float_,
                cv.Optional(CONF_STEP, default=1): cv.positive_float,
                cv.Optional(CONF_DEVICE_CLASS, default=DEVICE_CLASS_TEMPERATURE): cv.string,
                cv.Optional(CONF_UNIT_OF_MEASUREMENT, default=UNIT_CELSIUS): cv.string,
            }),
        }

    )
)


async def setup_conf(config, key, hub):
    if key in config:
        conf = config[key]

        num = await number.new_number(
            conf,
            min_value=conf[CONF_MIN_VALUE],
            max_value=conf[CONF_MAX_VALUE], 
            step=conf[CONF_STEP])
        cg.add(getattr(hub, "register_number")(key, num))
        cg.add(num.set_parent(hub))
        cg.add(num.set_internal_id(key))


async def to_code(config):
    hub = await cg.get_variable(config[CONF_EKHHE_ID])
    for key in TYPES:
        await setup_conf(config, key, hub)

