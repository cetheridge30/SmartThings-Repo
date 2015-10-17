/**
 *  Arduino Contact Sensor Monitor
 *
 *  Author: Christopher Etheridge
 *  Date: 2015-10-17
 */

metadata {

    definition (name: "Arduino Contact Sensor Monitor", author: "Chrisotpher Etheridge") {
        
        fingerprint profileId: "0104", deviceId: "0138", inClusters: "0000"
        
        capability "Sensor"
        capability "Contact Sensor"

        attribute "office",   "string"
        attribute "diningroom",  "string"
        attribute "bedroom", "string"
        attribute "livingroom", "string"
        attribute "kitchen", "string"
        attribute "frontdoor", "string"
        attribute "backdoor",  "string"
        attribute "garagedoor", "string"

        command "poll"

    }

    simulator {
    }

    // Preferences

    // tile definitions
    tiles {

        standardTile("office", "device.office", width: 1, height: 1, canChangeIcon: true, canChangeBackground: true) {
            state "closed",  label: "Closed",  icon: "st.contact.contact.closed",      backgroundColor: "#79b821"
            state "open",    label: "Open",    icon: "st.contact.contact.open",        backgroundColor: "#ffa81e"
        }
        
       	standardTile("diningroom", "device.diningroom", width: 1, height: 1, canChangeIcon: true, canChangeBackground: true) {
            state "closed",  label: "Closed",  icon: "st.contact.contact.closed",      backgroundColor: "#79b821"
            state "open",    label: "Open",    icon: "st.contact.contact.open",        backgroundColor: "#ffa81e"
        }


        standardTile("bedroom", "device.bedroom", width: 1, height: 1, canChangeIcon: true, canChangeBackground: true) {
            state "closed",  label: "Closed",  icon: "st.contact.contact.closed",      backgroundColor: "#79b821"
            state "open",    label: "Open",    icon: "st.contact.contact.open",        backgroundColor: "#ffa81e"
        }


        standardTile("livingroom", "device.livingroom", width: 1, height: 1, canChangeIcon: true, canChangeBackground: true) {
            state "closed",  label: "Closed",  icon: "st.contact.contact.closed",      backgroundColor: "#79b821"
            state "open",    label: "Open",    icon: "st.contact.contact.open",        backgroundColor: "#ffa81e"
        }


        standardTile("kitchen", "device.kitchen", width: 1, height: 1, canChangeIcon: true, canChangeBackground: true) {
            state "closed",  label: "Closed",  icon: "st.contact.contact.closed",      backgroundColor: "#79b821"
            state "open",    label: "Open",    icon: "st.contact.contact.open",        backgroundColor: "#ffa81e"
        }


        standardTile("frontdoor", "device.frontdoor", width: 1, height: 1, canChangeIcon: true, canChangeBackground: true) {
            state "closed",  label: "Closed",  icon: "st.contact.contact.closed",      backgroundColor: "#79b821"
            state "open",    label: "Open",    icon: "st.contact.contact.open",        backgroundColor: "#ffa81e"
        }

        standardTile("backdoor", "device.backdoor", width: 1, height: 1, canChangeIcon: true, canChangeBackground: true) {
            state "closed",  label: "Closed",  icon: "st.contact.contact.closed",      backgroundColor: "#79b821"
            state "open",    label: "Open",    icon: "st.contact.contact.open",        backgroundColor: "#ffa81e"
        }


        standardTile("garagedoor", "device.garagedoor", width: 1, height: 1, canChangeIcon: true, canChangeBackground: true) {
            state "closed",  label: "Closed",  icon: "st.contact.contact.closed",      backgroundColor: "#79b821"
            state "open",    label: "Open",    icon: "st.contact.contact.open",        backgroundColor: "#ffa81e"
        }


        main(["office","diningroom","bedroom","livingroom","kitchen","frontdoor","backdoor","garagedoor"])

        details(["office","diningroom","bedroom","livingroom","kitchen","frontdoor","backdoor","garagedoor"])
    }

}

def parse(String description) {
    def msg = zigbee.parse(description)?.text
    log.debug "Parse got '${msg}'"

    def parts = msg.split(" ")
    def name  = parts.length>0?parts[0].trim():null
    def value = parts.length>1?parts[1].trim():null

    name = value != "ping" ? name : null

    def result = createEvent(name: name, value: value)

    log.debug result

    return result
}

def poll() {
    log.debug "Polling requested"
    zigbee.smartShield(text: "poll").format()
}


