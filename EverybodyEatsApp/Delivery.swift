//
//  Delivery.swift
//  ErryBody Eats
//
//  Created by Daniyal Khan on 11/15/20.
//

import Foundation
import SwiftUI

struct Delivery: Identifiable {
    var id: String = ""
    var driver_id: String = ""
    var name: String = ""
    var rating: NSNumber = 0
    var notes: String = ""
    var restaurant: String = ""
    var time_window: NSNumber = 0
}
