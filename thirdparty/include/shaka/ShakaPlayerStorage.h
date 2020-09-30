// Copyright 2019 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef SHAKA_EMBEDDED_SHAKA_PLAYER_STORAGE_H_
#define SHAKA_EMBEDDED_SHAKA_PLAYER_STORAGE_H_

#import <Foundation/Foundation.h>

#include "macros.h"
#include "offline_externs_objc.h"
#include "ShakaPlayer.h"


NS_ASSUME_NONNULL_BEGIN

/**
 * Defines an interface for Storage events.
 */
SHAKA_EXPORT
@protocol ShakaPlayerStorageClient <NSObject>

@optional

/**
 * Called periodically with progress of a store or delete operation.
 */
- (void)onStorageProgress:(double)progress
              withContent:(ShakaStoredContent *)content;

@end

/**
 * Represents a JavaScript shaka.offline.Storage instance.  This handles
 * storing, listing, and deleting stored content.
 * @ingroup player
 */
SHAKA_EXPORT
@interface ShakaPlayerStorage : NSObject

- (nullable instancetype)initWithError:(NSError * _Nullable __autoreleasing * _Nullable)error NS_SWIFT_NAME(init());
- (nullable instancetype)initWithPlayer:(ShakaPlayer * _Nullable) player
                               andError:(NSError * _Nullable __autoreleasing * _Nullable)error NS_SWIFT_NAME(init(player:));

/** A client that receives events during storage. */
@property(atomic, weak, nullable) id<ShakaPlayerStorageClient> client;

/** Returns true if an asset is currently downloading. */
@property(atomic, readonly) BOOL storeInProgress;

/**
 * Request that this object be destroyed, releasing all resources and shutting
 * down all operations.
 */
- (void)destroyWithBlock:(ShakaPlayerAsyncBlock) block;

/**
 * Lists all the stored content available.  This gives an array of structures
 * representing all stored content. The <code>offlineUri</code> member of the
 * structure is the URI that should be given to <code>Player::Load()</code> to
 * play this piece of content offline.
 */
- (void)listWithBlock:(void (^)(NSArray<ShakaStoredContent *> *,
                                ShakaPlayerError * _Nullable)) block;

/**
 * Removes the given stored content. This will also attempt to release the
 * licenses, if any.
 */
- (void)remove:(NSString *)content_uri withBlock:(ShakaPlayerAsyncBlock) block;

/**
 * Removes any EME sessions that were not successfully removed before. This
 * gives whether all the sessions were successfully removed.
 */
- (void)removeEmeSessionsWithBlock:(void (^)(BOOL, ShakaPlayerError * _Nullable)) block;

/**
 * Stores the given manifest. If the content is encrypted, and encrypted
 * content cannot be stored on this platform, the Promise will be rejected
 * with error code 6001, REQUESTED_KEY_SYSTEM_CONFIG_UNAVAILABLE.
 */
- (void) store:(NSString*)uri
     withBlock:(void (^)(ShakaStoredContent *, ShakaPlayerError * _Nullable)) block;

/**
 * Stores the given manifest.  This also stores the given data along side the
 * media data so the app can store additional data.
 */
- (void)store:(NSString *)uri
    withAppMetadata:(NSDictionary<NSString *, NSString *> *)data
           andBlock:(void (^)(ShakaStoredContent *, ShakaPlayerError * _Nullable))block;


/**
 * Applies a configuration.
 *
 * @param namePath The path of the parameter to configure.
 *   I.e. @"manifest.dash.defaultPresentationDelay" corresponds to
 *   {manifest: {dash: {defaultPresentationDelay: *your value*}}}
 * @param value The value you wish to assign.
 */
- (void)configure:(const NSString *)namePath withBool:(BOOL)value;

/**
 * Applies a configuration.
 *
 * @param namePath The path of the parameter to configure.
 *   I.e. @"manifest.dash.defaultPresentationDelay" corresponds to
 *   {manifest: {dash: {defaultPresentationDelay: *your value*}}}
 * @param value The value you wish to assign.
 */
- (void)configure:(const NSString *)namePath withDouble:(double)value;

/**
 * Applies a configuration.
 *
 * @param namePath The path of the parameter to configure.
 *   I.e. @"manifest.dash.defaultPresentationDelay" corresponds to
 *   {manifest: {dash: {defaultPresentationDelay: *your value*}}}
 * @param value The value you wish to assign.
 */
- (void)configure:(const NSString *)namePath withString:(const NSString *)value;

/**
 * Returns a configuration to the default value.
 *
 * @param namePath The path of the parameter to configure.
 *   I.e. @"manifest.dash.defaultPresentationDelay" corresponds to
 *   {manifest: {dash: {defaultPresentationDelay: *your value*}}}
 */
- (void)configureWithDefault:(const NSString *)namePath;

@end

NS_ASSUME_NONNULL_END
#endif  // SHAKA_EMBEDDED_SHAKA_PLAYER_STORAGE_H_
