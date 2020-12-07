//
//  Order.swift
//  ErryBody Eats
//
//  Created by Daniyal Khan on 11/15/20.
//

import SwiftUI

struct Order: Identifiable {
    var id: String = ""
    var deliveryID: String = ""
    var customerID: String = ""
    var order: String = ""
    var name: String = ""
    var rating : NSNumber = 0
    var restaurant: String = ""
}
